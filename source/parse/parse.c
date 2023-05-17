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

/*t_errno	parse(t_msh *msh, t_list **tokens)
{
	t_cmd	*cmd;
	t_errno	errno;

	while (*tokens)
	{
		cmd = cmd_init(0, NULL);
		if (cmd == NULL)
			return (MSH_MEMFAIL);
		errno = parse_cmd(cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (cmd_free_list(cmd), errno);
		errno = cmd_argvconvert(cmd);
		if (errno != MSH_SUCCESS)
			return (cmd_free_list(cmd), errno);
		errno = list_append_ptr(msh->cmds, cmd) != MSH_SUCCESS;
		if (errno != MSH_SUCCESS)
			return (cmd_free(cmd), errno);
	}
	return (MSH_SUCCESS);
}*/

t_errno	parse(t_msh *msh, t_list **tokens)
{
	t_toktype			type;
	t_parsefunc const	parsefuncs[N_TOK] = {
		parse_word,
		parse_input, parse_heredoc,
		parse_output, parse_output_append,
		parse_pipe, parse_and, parse_or,
		parse_invalid};
	t_errno				errno;

	while (*tokens)
	{
		type = ((t_token *)(*tokens)->content)->type;
		errno = parsefuncs[type](&msh->cmds, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (errno);
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
