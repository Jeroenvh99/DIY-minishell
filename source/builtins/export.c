/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/09 16:54:17 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_stdio.h"
#include <fcntl.h>
#include <unistd.h>

int	get_fd(char *name)
{
	int	fd;

	fd = open(name, O_CREAT);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	msh_export(int argc, char **argv, t_msh *msh)
{
	int		i;
	int		j;
	int		fd;
	char	*var;

	if (argc == 0)
	{
		fd = get_fd(msh->output);
		fd = 0;
		if (fd == -1)
			return (1);
		i = 0;
		while (msh->env[i])
		{
			write(fd, "declare -x ", 11);
			j = 0;
			while (msh->env[i][j])
			{
				if (msh->env[i][j] == '=')
				{
					++j;
					break ;
				}
				++j;
			}
			write(fd, msh->env[i], j);
			ft_dprintf(fd, "\"%s\"\n", msh->env[i] + j);
			++i;
		}
		close(fd);
		return (0);
	}
	else
	{
		i = 0;
		while (argc[i])
		{
			var = hashtable_pop(msh->loc_var, argc[i]);
			if (msh->envused < msh->envspc)
			{
				msh->env[msh->envused] = var;
				++(msh->envused);
			}
			else
			{
				// reallocate env and copy the old env to the new env
				// update envspc and envused
			}
			++i;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	msh_export(argc, argv, envp);
}