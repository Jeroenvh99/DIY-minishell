/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/29 10:32:42 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"

int	check_n_opt(char *str)
{
	size_t	i;

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

int	write_args(t_cmd *cmd, size_t i)
{
	while (i < cmd->argc)
	{
		ft_dprintf(cmd->io[1], "%s", cmd->argv.array[i]);
		if (i != cmd->argc - 1)
			ft_dprintf(cmd->io[1], " ");
		++i;
	}
	return (0);
}

int	msh_echo(t_cmd *cmd, t_msh *msh)
{
	size_t	i;
	int		newline;

	(void)msh;
	i = 1;
	newline = 1;
	while (i < cmd->argc && check_n_opt(cmd->argv.array[i]))
	{
		newline = 0;
		++i;
	}
	write_args(cmd, i);
	if (newline)
	{
		ft_dprintf(cmd->io[1], "\n");
	}
	return (0);
}
