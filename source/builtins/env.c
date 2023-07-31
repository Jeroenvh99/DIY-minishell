/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/18 16:51:19 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "msh.h"

void	env_error(int fd, char *arg)
{
	ft_dprintf(fd, "env: %s: No such file or directory\n", arg);
}

void	print_2d_arr(int fd, char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_dprintf(fd, "%s\n", arr[i]);
		++i;
	}
}

int	msh_env(t_cmd *cmd, t_msh *msh)
{
	if (cmd->argc > 1)
	{
		if (i == cmd->argc - 1)
		{
			env_error(cmd->io[IO_ERR], cmd->argv.array[i]);
			return (127);
		}
		++i;
	}
	print_2d_arr(cmd->io[IO_OUT], msh->env.envp, msh->env.len);
	return (0);
}
/*DB: De handleiding stelt dat deze functie ook programma's moet uitvoeren
 * met de als variabele opgegeven waarden als omgevingsvariabelen. Die moeten
 * dan niet blijven staan voor het volgende commando! Dus:
 * $env lorem=ipsum dolor | sit		-> 'dolor' kan de waarde van lorem zien
 * 									maar 'sit' kan dat niet.
 */
