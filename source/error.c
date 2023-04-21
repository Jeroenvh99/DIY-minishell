/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 18:27:29 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/21 16:08:27 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../lib/libft/include/ft_string.h"
#include <unistd.h>

void	print_error(char *command, char *argument, char *message)
{
	write(2, "msh: ", 5);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	if (argument)
	{
		write(2, argument, ft_strlen(argument));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
