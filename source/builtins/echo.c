/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:16:12 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/18 18:04:08 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argc > 1 && ft_strncmp(argv[i], "-n", 3) == 0)
	{
		newline = 0;
		++i;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		++i;
	}
	if (newline)
		write(1, "\n", 1);
	return (1);
}
