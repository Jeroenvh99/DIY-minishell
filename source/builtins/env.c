/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/08 16:06:57 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_msh
{
	char	**env;
	int		last_status;
}			t_msh;

void	print_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		++i;
	}
}

int	msh_env(int argc, char **argv, t_msh *msh)
{
	print_2d_arr(msh->env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh *msh;

	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = envp;
	msh_env(argc, argv, msh);
}