/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 13:58:40 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_string.h"

static t_errno	parse_invalid(t_list **cmds, t_list **tokens, t_msh *msh);

t_errno	parse(t_msh *msh, t_list **tokens)
{
	t_toktype			type;
	t_parsefunc const	parsefuncs[N_TOK] = {
		parse_word, parse_pipe,
		parse_input, parse_heredoc,
		parse_output, parse_output_append,
		parse_and, parse_or,
		parse_invalid};
	t_errno				errno;

	errno = MSH_SUCCESS;
	while (*tokens)
	{
		type = ((t_token *)(*tokens)->content)->type;
		errno = parsefuncs[type](&msh->cmds, tokens, msh);
		if (errno != MSH_SUCCESS)
			break ;
	}
	return (cmd_argvconvert(cmd_get_current(msh->cmds)));
}

static t_errno	parse_invalid(t_list **cmds, t_list **tokens, t_msh *msh)
{
	(void) cmds;
	(void) tokens;
	(void) msh;
	return (MSH_SYNTAX_ERROR);
}
