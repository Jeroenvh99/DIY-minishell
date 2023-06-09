/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/04/18 18:27:29 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/06 15:44:50 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_error.h"

#include "ft_stdio.h"
#include "ft_string.h"
#include <unistd.h>

void	msh_strerror(t_errno errno)
{
	char const *const	errmsg[N_ERRNO] = {
		"Everything went better than expected.",
		"NOCMDLINE",
		"ENDCMD_PIPE",
		"ENDCMD_CTL",
		"Something went wrong.",
		"Syntax error.",
		"NO_VARSTR",
		"INCOMPLETE_TOKEN",
		"Failed to open file.",
		"Couldn't allocate memory.",};

	ft_dprintf(STDERR_FILENO, "Error: %s\n", errmsg[errno]);
}

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
