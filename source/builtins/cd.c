/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/21 16:25:39 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*buf;
	char	*folder;
	char	*newdir;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		return (1);
	folder = ft_strjoin("/", argv[1]);
	newdir = ft_strjoin(buf, folder);
	free(folder);
	free(buf);
	chdir(newdir);
	// update env
}
