/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/04/18 18:27:29 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/11 15:57:54 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_error.h"

#include "ft_stdio.h"
#include "ft_string.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

void	msh_strerror(t_errno errno)
{
	char const *const	errmsg[N_ERRNO] = {
		"Everything went better than expected.",
		"ENDCMD_PIPE",
		"ENDCMD_CTL",
		"Something went wrong.",
		"Syntax error.",
		"Invalid identifier",
		"INCOMPLETE_TOKEN",
		"End of file encountered.",
		"Failed to establish pipeline.",
		"Failed to open file.",
		"Couldn't create fork.",
		"Couldn't allocate memory.",};

	ft_dprintf(STDERR_FILENO, "msh: %s\n", errmsg[errno]);
}

void	msh_perror(unsigned int n, ...)
{
	va_list		ap;

	va_start(ap, n);
	ft_dprintf(2, "msh: ");
	while (n--)
		ft_dprintf(2, "%s: ", va_arg(ap, char *));
	va_end(ap);
	perror("");
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
