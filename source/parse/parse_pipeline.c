/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/22 21:45:29 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_string.h"
#include <unistd.h>

/* Parse `tokens` to create a pipeline, consisting of a linked list of simple
 * commands. At least a part of `tokens` is consumed in the process.
 */
t_errno	parse_pipeline(t_list **pipeline, t_list **tokens, t_msh *msh)
{
	t_errno	errno;
	t_cmd	*cmd;

	while (*tokens && !is_ctltok((*tokens)->content))
	{
		cmd = cmd_init(0, NULL);
		if (cmd == NULL)
			return (MSH_MEMFAIL);
		cmd->io[IO_IN] = STDIN_FILENO;
		errno = parse_cmd(cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
		if (list_append_ptr(pipeline, cmd) != 0)
			return (list_clear(pipeline, (t_freef)cmd_free), cmd_free(cmd),
				MSH_MEMFAIL);
		errno = parse_pipe(cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
	}
	return (MSH_SUCCESS);
}
