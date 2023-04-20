/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/20 14:10:22 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"
#include "./../../lib/libft/include/ft_ctype.h"
#include "./../../lib/libft/include/ft_stdlib.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	status;
	int	i;

	status = 0;
	if (argc > 2)
	{
		write(2, "exit\n", 5);
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	else if (argc == 2)
	{
		i = 0;
		while (argv[1][i])
		{
			if (ft_isalpha(argv[1][i]))
			{
				write(2, "exit\n", 5);
				print_error("exit", argv[1], "numeric argument required");
				return (1);
			}
			++i;
		}
		status = ft_atoi(argv[1]);
	}
	exit(status);
}
