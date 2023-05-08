/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/08 15:01:38 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <unistd.h>

int	msh_echo(int argc, char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-n", 3) == 0)
		{
			newline = 0;
		}
		else
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (argv[i + 1])
				write(1, " ", 1);
		}
		++i;
	}
	if (newline)
		write(1, "\n", 1);
	return (1);
}

int main(int argc, char **argv)
{
	msh_echo(argc, argv);
}