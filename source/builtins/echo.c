/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/25 11:28:45 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
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

void	write_args(t_cmd *cmd, int i)
{
	while (cmd->argv.array[i])
	{
		if (write(cmd->io.out, cmd->argv.array[i],
				ft_strlen(cmd->argv.array[i])) == -1)
			return (-1);
		if (cmd->argv.array[i + 1])
		{
			if (write(cmd->io.out, " ", 1) == -1)
				return (-1);
		}
		++i;
	}
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
	write_args(cmd, i);
	if (newline)
	{
		if (write(cmd->io.out, "\n", 1) == -1)
			return (-1);
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	msh_echo(argc, argv);
// }