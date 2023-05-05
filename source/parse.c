/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:56:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_string.h"

static t_errno	parse_invalid(t_list **tokens, t_list **cmds);

t_errno	parse(t_list **tokens, t_list **cmds)
{
	t_toktype			type;
	t_parsefunc const	parsefuncs[N_TOK] = {
		parse_word, parse_qword, parse_pipe,
		parse_input, parse_heredoc,
		parse_output, parse_output_append,
		parse_and, parse_or,
		parse_invalid};
	t_errno				errno;

	errno = MSH_SUCCESS;
	while (*tokens)
	{
		type = ((t_token *)(*tokens)->content)->type;
		errno = parsefuncs[type](tokens, cmds);
		if (errno != MSH_SUCCESS)
			break ;
	}
	return (errno);
}

static t_errno	parse_invalid(t_list **tokens, t_list **cmds)
{
	(void) tokens;
	(void) cmds;
	return (MSH_SYNTAX_ERROR);
}
