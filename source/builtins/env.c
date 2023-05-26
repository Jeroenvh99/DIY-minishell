/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/26 15:47:15 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <stdio.h>
#include <stdlib.h>

void	env_error(int fd, char *arg)
{
	ft_dprintf(fd, "env: %s: No such file or directory", arg);
}

int	ft_isonlydash(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '-')
		++i;
	return (str[i] == '\0' && i != 2);
}

int	msh_env(t_cmd *cmd, t_msh *msh)
{
	size_t	i;

	i = 1;
	while (cmd->argv.array[i])
	{
		if (cmd->argc == 2 && ft_strncmp(cmd->argv.array[i], "--", 3) == 0)
			break ;
		if (i == cmd->argc - 1 && !(i == 1 && ft_isonlydash(cmd->argv.array[i])))
		{
			env_error(cmd->io.err, cmd->argv.array[i]);
			return (127);
		}
		++i;
	}
	print_2d_arr(cmd->io.out, msh->env.envp);
	return (0);
}
