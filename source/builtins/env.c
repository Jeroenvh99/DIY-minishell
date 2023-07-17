/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/20 10:48:48 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "msh.h"
#include <stdio.h>
#include <stdlib.h>

void	env_error(int fd, char *arg)
{
	ft_dprintf(fd, "env: %s: No such file or directory\n", arg);
}

int	msh_env(t_cmd *cmd, t_msh *msh)
{
	size_t	i;

	i = 1;
	while (cmd->argv.array[i])
	{
		if (i == cmd->argc - 1)
		{
			env_error(cmd->io.err, cmd->argv.array[i]);
			return (127);
		}
		++i;
	}
	print_2d_arr(cmd->io.out, msh->env.envp, msh->env.len);
	return (0);
}
