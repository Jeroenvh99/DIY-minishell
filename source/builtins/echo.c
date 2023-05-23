/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/22 14:56:18 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <unistd.h>

int	msh_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->argv.array[i])
	{
		if (ft_strncmp(cmd->argv.array[i], "-n", 3) == 0)
		{
			newline = 0;
		}
		else
		{
			write(cmd->io->out, cmd->argv.array[i], ft_strlen(cmd->argv.array[i]));
			if (cmd->argv.array[i + 1])
				write(cmd->io->out, " ", 1);
		}
		++i;
	}
	if (newline)
		write(cmd->io->out, "\n", 1);
	return (1);
}

int main(int argc, char **argv)
{
	msh_echo(argc, argv);
}