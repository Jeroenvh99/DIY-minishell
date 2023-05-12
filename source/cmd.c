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

t_cmd	*cmd_init(size_t argc, char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->argc = argc;
	cmd->argv = argv;
	return (cmd);
}

void	cmd_free(t_cmd *cmd)
{
	while (cmd->argc)
		free(cmd->argv[--cmd->argc]);
	free(cmd->argv);
	free(cmd);
}

void	cmd_destroy(t_cmd **cmd)
{
	cmd_free(*cmd);
	*cmd = NULL;
}
