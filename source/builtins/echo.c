/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/23 13:17:36 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <unistd.h>

int	msh_echo(t_cmd *cmd, t_msh *msh)
{
	int	i;
	int	newline;
	int	content;

	(void)msh;
	i = 1;
	newline = 1;
	content = 0;
	while (cmd->argv.array[i])
	{
		if (content == 0 && ft_strncmp(cmd->argv.array[i], "-n", 3) == 0)
		{
			newline = 0;
		}
		else
		{
			if (write(cmd->io->out, cmd->argv.array[i],
					ft_strlen(cmd->argv.array[i])) == -1)
				return (-1);
			if (cmd->argv.array[i + 1])
			{
				if (write(cmd->io->out, " ", 1) == -1)
					return (-1);
			}
			content = 1;
		}
		++i;
	}
	if (newline)
	{
		if (write(cmd->io->out, "\n", 1) == -1)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	msh_echo(argc, argv);
}