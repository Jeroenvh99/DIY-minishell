/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/19 18:10:30 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"
#include "./../../lib/libft/include/ft_string.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	status;

	status = 0;
	if (not_numeric)
	{
		print_error("exit", argv[1], "numeric argument required");
	}
	if (argc > 2)
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	else
		exit(status);
	return (0);
}
