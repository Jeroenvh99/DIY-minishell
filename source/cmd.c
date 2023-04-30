/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_utils.h"

#include <stddef.h>
#include <stdlib.h>

t_cmd	*cmd_init(char *path, size_t argc, char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->path = path;
	cmd->argc = argc;
	cmd->argv = argv;
	return (cmd);
}

void	cmd_destroy(t_cmd **cmd)
{
	free((*cmd)->path);
	free_ptr_array((void **)(*cmd)->argv, (*cmd)->argc);
	free(*cmd);
	*cmd = NULL;
}
