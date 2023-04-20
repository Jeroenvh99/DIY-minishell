/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/20 14:24:31 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"
#include "./../../lib/libft/include/ft_ctype.h"
#include "./../../lib/libft/include/ft_stdlib.h"
#include <stdlib.h>
#include <unistd.h>

int	check_arg(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
		{
			write(2, "exit\n", 5);
			print_error("exit", argv[1], "numeric argument required");
			return (0);
		}
		++str;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	status;

	status = 0;
	if (argc > 2)
	{
		write(2, "exit\n", 5);
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	else if (argc == 2)
	{
		if (!check_arg(argv[1]))
			return (1);
		status = ft_atoi(argv[1]);
	}
	exit(status);
}
