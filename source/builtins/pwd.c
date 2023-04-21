/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:27:41 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/21 11:16:20 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int	main(int argc, char **argv)
{
	DIR				*cdir;
	char			*buf;
	struct dirent	*dir;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		write(1, buf, ft_strlen(buf));
		cdir = opendir(buf);
		dir = readdir(cdir);
		write(1, dir->d_name, ft_strlen(dir->d_name));
		closedir(cdir);
		free(buf);
		return (0);
	}
	else
		return (1);
}