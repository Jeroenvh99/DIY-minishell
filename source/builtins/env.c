/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/12 15:57:59 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	msh_env(int argc, char **argv, t_msh *msh)
{
	if (argc > 1)
	{
		error
		return (1);
	}
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