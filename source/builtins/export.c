/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/07 15:25:40 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "msh.h"
#include <fcntl.h>
#include <stdio.h>

static int	exp_print_env(t_env *env);

int	msh_export(t_cmd *cmd, t_msh *msh)
{
	int	i;

	if (cmd->argc == 1)
	{
		if (exp_print_env(&msh->env) == -1)
			return (-1);
	}
	i = 1;
	while (cmd->argv.array[i])
	{
		env_set_entry(&msh->env, cmd->argv.array[i]);
		++i;
	}
	return (0);
}

static int	exp_print_env(t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (env->envp[i])
	{
		if (printf("declare -x ") == -1)
			return (-1);
		j = 0;
		while (env->envp[i][j])
		{
			if (env->envp[i][j] == '=')
				break ;
			++j;
		}
		if (printf("%.*s", j + 1, env->envp[i]) == -1)
			return (-1);
		printf("\"%s\"\n", env->envp[i] + j + 1);
		++i;
	}
	return (0);
}
