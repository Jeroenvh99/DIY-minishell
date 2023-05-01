/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 13:59:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:57:49 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "ft_stdlib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static inline bool	cmd_is_undef(t_cmd *cmd);

t_errno	parse_pipe(t_list **tokens, t_list **cmds)
{
	t_cmd	*pipe_to;

	free(token_pop(tokens));
	if (cmd_is_undef(cmd_get_current(*cmds)))
		return (MSH_SYNTAX_ERROR);
	if (*tokens == NULL && input_get(tokens, PROMPT_PIPE) != MSH_SUCCESS)
		return (MSH_MEMFAIL);
	pipe_to = ft_calloc(1, sizeof(t_cmd));
	if (pipe_to == NULL)
		return (MSH_MEMFAIL);
	if (list_append_ptr(cmds, pipe_to) != MSH_SUCCESS)
		return (free(pipe_to), MSH_MEMFAIL);
	return (MSH_SUCCESS);
}

static inline bool	cmd_is_undef(t_cmd *cmd)
{
	return (!(cmd && (cmd->path
				|| cmd->io.in_mode
				|| cmd->io.out_mode
				|| cmd->io.err_mode)));
}
