/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/18 18:42:08 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include "./../include/minishell.h"
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
		return ;
	}
	else
		exit();
}
