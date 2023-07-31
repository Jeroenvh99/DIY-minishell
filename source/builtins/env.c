/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/06 16:48:31 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "msh.h"

void	env_error(int fd, char *arg)
{
	ft_dprintf(fd, "env: %s: No such file or directory\n", arg);
}

int	msh_env(t_cmd *cmd, t_msh *msh)
{
	if (cmd->argc > 1)
	{
		env_error(cmd->io[2], cmd->argv.array[cmd->argc - 1]);
		return (127);
	}
	print_2d_arr(cmd->io[1], msh->env.envp, msh->env.len);
	return (0);
}
