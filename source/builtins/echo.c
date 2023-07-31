/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/05 11:06:36 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <unistd.h>

int	check_n_opt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != '-')
			return (0);
		if (i > 0 && str[i] != 'n')
			return (0);
		++i;
	}
	return (1);
}

int	write_args(t_cmd *cmd, int i)
{
	while (cmd->argv.array[i])
	{
		if (ft_dprintf(cmd->io[1], "%s", cmd->argv.array[i]) == -1)
			return (-1);
		if (cmd->argv.array[i + 1])
		{
			if (write(cmd->io[1], " ", 1) == -1)
				return (-1);
		}
		++i;
	}
	return (0);
}

int	msh_echo(t_cmd *cmd, t_msh *msh)
{
	int	i;
	int	newline;

	(void)msh;
	i = 1;
	newline = 1;
	while (cmd->argv.array[i] && check_n_opt(cmd->argv.array[i]))
	{
		newline = 0;
		++i;
	}
	if (write_args(cmd, i) == -1)
		return (-1);
	if (newline)
	{
		if (write(cmd->io[1], "\n", 1) == -1)
			return (-1);
	}
	return (0);
}
