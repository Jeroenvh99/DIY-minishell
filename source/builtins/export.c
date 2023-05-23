/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/15 16:44:38 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_stdio.h"
#include <fcntl.h>
#include <unistd.h>

void	exp_print_env(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (msh->env[i])
	{
		write(msh->outfd, "declare -x ", 11);
		j = 0;
		while (msh->env[i][j])
		{
			if (msh->env[i][j] == '=')
				break ;
			++j;
		}
		write(msh->outfd, msh->env[i], j + 1);
		ft_printf("\"%s\"\n", msh->env[i] + j + 1);
		++i;
	}
	close(msh->outfd);
}

void	realloc_env(t_msh *msh, int extra_size)
{
	int		i;
	char	**new_env;

	msh->envspc += extra_size;
	i = msh->envspc;
	new_env = (char **)malloc(i * sizeof(char *));
	--i;
	new_env[i] = NULL;
	i -= extra_size;
	while (i > -1)
	{
		new_env[i] = msh->env[i];
		--i;
	}
	free(msh->env);
	msh->env = new_env;
}

int	msh_export(int argc, char **argv, t_msh *msh)
{
	int		i;
	int		j;
	char	*var;

	if (argc == 0)
		exp_print_env(msh);
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '-'))
			return (0); // usage message
		if (ft_strchr(argv[i], '='))
		{
			if (msh->envused == msh->envspc)
				realloc_env(msh, argc - 1 - i);
			var = ft_strdup(argv[i]);
			msh->env[msh->envused] = var;
			++(msh->envused);
		}
		++i;
	}
	return (0);
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