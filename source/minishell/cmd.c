/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 17:51:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static void	cmd_free_common(t_cmd *cmd);

t_cmd	*cmd_init(size_t argc, char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->argc = argc;
	cmd->argv.array = argv;
	cmd->io.in = -1;
	cmd->io.out = -1;
	cmd->io.err = -1;
	return (cmd);
}

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

static void	cmd_free_common(t_cmd *cmd)
{
	if (cmd->io.in != STDIN_FILENO)
		close(cmd->io.in);
	if (cmd->io.out != STDOUT_FILENO)
		close(cmd->io.out);
	if (cmd->io.err != STDERR_FILENO)
		close(cmd->io.err);
	free(cmd);
}
