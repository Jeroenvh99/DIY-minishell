/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/21 11:48:17 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "msh.h"
#include <fcntl.h>
#include <unistd.h>

int	exp_print_env(t_msh *msh, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (msh->env[i])
	{
		if (write(cmd->io[1], "declare -x ", 11) == -1)
			return (-1);
		j = 0;
		while (msh->env[i][j])
		{
			if (msh->env[i][j] == '=')
				break ;
			++j;
		}
		if (write(cmd->io[1], msh->env[i], j + 1) == -1)
			return (-1);
		ft_dprintf(cmd->io[1], "\"%s\"\n", msh->env[i] + j + 1);
		++i;
	}
	return (0);
}

int	msh_export(t_cmd *cmd, t_msh *msh)
{
	int	i;

	if (cmd->argc == 1)
	{
		if (exp_print_env(msh, cmd) == -1)
			return (-1);
	}
	i = 1;
	while (cmd->argv.array[i])
	{
		if (ft_strchr(cmd->argv.array[i], '='))
            env_set(msh->env, (const char)cmd->argv.array[i]);
		++i;
	}
	return (0);
}
