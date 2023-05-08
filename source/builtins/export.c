/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/08 18:13:43 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_stdio.h"
#include <unistd.h>
#include <fcntl.h>

int	get_fd(char *name)
{
	int	fd;

	fd = open(name, O_CREAT);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	msh_export(int argc, char **argv, char **argv)
{
	int	i;
	int	j;
	int	fd;

	if (argc == 0)
	{
		fd = get_fd(msh->output);
		fd = 0;
		if (fd == -1)
			return (1);
		i = 0;
		while (argv[i])
		{
			write(fd, "declare -x ", 11);
			j = 0;
			while (argv[i][j])
			{
				if (argv[i][j] == '=')
				{
					++j;
					break ;
				}
				++j;
			}
			write(fd, argv[i], j);
			ft_dprintf(fd, "\"%s\"\n", argv[i] + j);
			++i;
		}
		close(fd);
		return (0);
	}
	// fetch variable from local variables
	// insert variable into env
}

int	main(int argc, char **argv, char **envp)
{
	msh_export(argc, argv, envp);
}