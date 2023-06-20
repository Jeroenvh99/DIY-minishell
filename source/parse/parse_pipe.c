/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 13:59:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/20 14:37:36 by dbasting      ########   odam.nl         */
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
#include <unistd.h>

static inline int	cmd_is_undefined(t_cmd *cmd);

t_errno	parse_pipe(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	(void) msh;
	if (*tokens == NULL || ((t_token *)((*tokens)->content))->type != TOK_PIPE)
		return (MSH_SUCCESS);
	if (cmd_is_undefined(cmd))
		return (MSH_SYNTAX_ERROR);
	token_free(list_pop_ptr(tokens));
	return (MSH_SUCCESS);
}

static inline int	cmd_is_undefined(t_cmd *cmd)
{
	return (!cmd || (cmd->argc == 0
			&& cmd->io[IO_IN] == STDIN_FILENO
			&& cmd->io[IO_OUT] == STDOUT_FILENO
			&& cmd->io[IO_ERR] == STDERR_FILENO));
}
