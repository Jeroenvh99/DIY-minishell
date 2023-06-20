/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/20 21:54:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_string.h"
#include <unistd.h>

/* Parse `tokens` to form a command tree. `tokens` is consumed. */
// N.B. Momenteel kan-ie alleen pipelines maken; ()&&|| volgt.
t_errno	parse(t_msh *msh, t_list **tokens)
{
	t_list	**pipeline;
	t_errno	errno;

	pipeline = &msh->cmds;
	while (*tokens)
	{
		if (is_ctltok((*tokens)->content))
			token_free(list_pop_ptr(tokens));
		errno = parse_pipeline(pipeline, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (errno);
	}
	return (MSH_SUCCESS);
}

/* Parse `tokens` to create a pipeline, consisting of a linked list of simple
 * commands. At least a part of `tokens` is consumed in the process.
 */
t_errno	parse_pipeline(t_list **pipeline, t_list **tokens, t_msh *msh)
{
	t_errno	errno;
	t_cmd	*cmd;
	t_fd	fitting;

	fitting = STDIN_FILENO;
	while (*tokens && !is_ctltok((*tokens)->content))
	{
		cmd = cmd_init(0, NULL);
		if (cmd == NULL)
			return (MSH_MEMFAIL);
		cmd->io[IO_IN] = fitting;
		errno = parse_cmd(cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
		errno = list_append_ptr(pipeline, cmd);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), cmd_free(cmd),
				errno);
		errno = parse_pipe(&fitting, cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
	}
	return (MSH_SUCCESS);
}

/* Throw an MSH_SYNTAX_ERROR if an invalid token is encountered. This should
 * never happen. If it does, the lexer is likely broken.
 */
t_errno	parse_invalid(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	(void) cmd;
	(void) tokens;
	(void) msh;
	return (MSH_SYNTAX_ERROR);
}
