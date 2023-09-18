/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 13:59:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/18 14:07:19 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static inline int	cmd_is_undefined(t_cmd *cmd);

/* Parse pipe: If `cmd` is to be followed by another command, create a pipe and
 * assign the write end as `cmd`'s output file (unless output has already been
 * redirected). Place the read end in `out`, so it can be set as the next
 * command's input file.
 * If there is no command to pipe to (i.e. there are no tokens left or the next
 * token is a control character), assign STDOUT_FILENO as `cmd`'s output file
 * (notwithstanding any previous redirections); don't create a pipe.
 */
t_errno	parse_pipe(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	(void) msh;
	if (*tokens == NULL || ((t_token *)((*tokens)->content))->type != TOK_PIPE)
	{
		if (cmd->io[IO_OUT] == -1)
			cmd->io[IO_OUT] = STDOUT_FILENO;
		return (MSH_SUCCESS);
	}
	if (cmd_is_undefined(cmd))
		return (MSH_SYNTAX_ERROR);
	token_free(list_pop_ptr(tokens));
	return (MSH_SUCCESS);
}

static inline int	cmd_is_undefined(t_cmd *cmd)
{
	return (!cmd || (cmd->argc == 0
			&& cmd->io[IO_IN] == -1
			&& cmd->io[IO_OUT] == -1
			&& cmd->io[IO_ERR] == STDERR_FILENO));
}
