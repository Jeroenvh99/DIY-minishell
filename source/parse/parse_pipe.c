/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 13:59:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 17:52:29 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

static inline int	cmd_is_undef(t_cmd *cmd);

t_errno	parse_pipe(t_list **cmds, t_list **tokens, t_msh *msh)
{
	t_cmd *const	pipe_from = cmd_get_current(*cmds);
	t_cmd			*pipe_to;

	(void) msh;
	free(list_pop_ptr(tokens));
	if (cmd_is_undef(pipe_from))
		return (MSH_SYNTAX_ERROR);
	if (cmd_argvconvert(pipe_from) != MSH_SUCCESS)
		return (MSH_MEMFAIL);
	if (*tokens == NULL && readcmdline(tokens, PROMPT_PIPE) != MSH_SUCCESS)
		return (MSH_MEMFAIL);
	pipe_to = ft_calloc(1, sizeof(t_cmd));
	if (pipe_to == NULL)
		return (MSH_MEMFAIL);
	if (list_append_ptr(cmds, pipe_to) != MSH_SUCCESS)
		return (free(pipe_to), MSH_MEMFAIL);
	return (MSH_SUCCESS);
}

static inline int	cmd_is_undef(t_cmd *cmd)
{
	return (!(cmd && (cmd->argv.list
				|| cmd->io.in_mode
				|| cmd->io.out_mode
				|| cmd->io.err_mode)));
}