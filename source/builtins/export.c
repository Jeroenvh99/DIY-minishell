/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/07 17:08:09 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	exp_print_env(t_env *env);

int	msh_export(t_cmd *cmd, t_msh *msh)
{
	int	i;

	if (cmd->argc == 1)
		exp_print_env(&msh->env);
	i = 1;
	while (cmd->argv.array[i])
	{
		if (env_set_entry(&msh->env, cmd->argv.array[i]) > 0)
		{
			ft_dprintf(STDERR_FILENO, "msh: export: `%s': not a valid "
				"identifier\n", cmd->argv.array[i]);
			return (1);
		}
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
		printf("declare -x ");
		j = 0;
		while (env->envp[i][j])
		{
			if (env->envp[i][j] == '=')
				break ;
			++j;
		}
		printf("%.*s", j + 1, env->envp[i]);
		printf("\"%s\"\n", env->envp[i] + j + 1);
		++i;
	}
	return (0);
}
