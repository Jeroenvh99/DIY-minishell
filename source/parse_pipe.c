/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 13:59:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:41:27 by dbasting      ########   odam.nl         */
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

static inline bool	cmd_is_undef(t_cmd *pipe_from);

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

static inline bool	cmd_is_undef(t_cmd *pipe_from)
{
	return (!(pipe_from && (pipe_from->path
			|| pipe_from->io.in_mode
			|| pipe_from->io.out_mode
			|| pipe_from->io.err_mode)));
}
