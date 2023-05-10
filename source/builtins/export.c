/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 17:52:53 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_stdio.h"
#include <fcntl.h>
#include <unistd.h>

char	**realloc_env(char **env, int curr_size, int extra_size)
{
	int		i;
	char	**new_env;

	i = curr_size + extra_size;
	new_env = (char **)malloc(i * sizeof(char *));
	--i;
	new_env[i] = NULL;
	i -= extra_size;
	while (i > -1)
	{
		new_env[i] = env[i];
		--i;
	}
	free(env);
	return (new_env);
}

int	msh_export(int argc, char **argv, t_msh *msh)
{
	int		i;
	int		j;
	char	*var;

	// check for invalid input
	if (argc == 0)
	{
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
			ft_printf("\"%s\"\n", msh->env[i] + j);
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
			if (msh->envused < msh->envspc)
			{
				var = hashtable_pop(msh->loc_var, argc[i]);
				msh->env[msh->envused] = var;
				++(msh->envused);
				++i;
			}
			else
			{
				msh->env = realloc_env(msh->env, msh->envspc, argc - 1);
				msh->envspc += argc - 1;
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msh *msh;
	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	msh->envspc = env_size(envp);
	msh->envused = msh->envspc;

	print_2d_arr(msh->env);
	msh_export(argc, argv, envp);
	print_2d_arr(msh->env);
}