/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:50:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/09 16:10:13 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include "./../../minishell.h"
#include <stdlib.h>

int	msh_unset(int argc, char **argv, t_msh *msh)
{
	int	i;
	int	j;

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i])
	{
		j = remove_var(argv[i], msh->env);
		if (msh->env[j])
		{
			while (msh->env[j + 1])
			{
				msh->env[j] = msh->env[j + 1];
				++j
			}
			msh->env[j - 1] = NULL;
		}
		++i;
	}
	--(msh->envused);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh *msh;
	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	msh->envspc = env_size(envp);
	msh->envused = msh->envspc;

	print_2d_arr(msh->env);
	msh_unset(argc, argv, msh);
	print_2d_arr(msh->env);
}