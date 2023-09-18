/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/15 14:35:39 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static inline void	cmd_free_common(t_cmd *cmd);

/**
 * @brief	Allocate and initialize a new command.
 */
t_cmd	*cmd_init(size_t argc, char **argv)
{
	t_cmd *const	cmd = malloc(sizeof(t_cmd));

	if (cmd == NULL)
		return (NULL);
	cmd->argc = argc;
	cmd->argv.array = argv;
	cmd->io[IO_IN] = -1;
	cmd->io[IO_OUT] = -1;
	cmd->io[IO_ERR] = -1;
	return (cmd);
}

/**
 * @brief	Deallocate a command. Associated nonstandard file descriptors are
 * 			closed.
 */
void	cmd_free(t_cmd *cmd)
{
	while (cmd->argc)
		free(cmd->argv.array[--cmd->argc]);
	free(cmd->argv.array);
	cmd_free_common(cmd);
}

void	cmd_free_list(t_cmd *cmd)
{
	list_clear(&cmd->argv.list, free);
	cmd_free_common(cmd);
}

static inline void	cmd_free_common(t_cmd *cmd)
{
	t_fd	fd;

	fd = 0;
	while (fd < N_IO)
	{
		if (cmd->io[fd] != fd)
			close(cmd->io[fd]);
		fd++;
	}
	free(cmd);
}
