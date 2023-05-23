/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:50:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/23 13:28:29 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include "./../../lib/libft/include/ft_stdio.h"
#include "./../../include/minishell.h"
#include <stdlib.h>

int	msh_unset(t_cmd *cmd, t_msh *msh)
{
	int	i;
	int	j;

	if (cmd->argc == 1)
		return (0);
	i = 1;
	while (cmd->argv.array[i])
	{
		if (!ft_strchr(cmd->argv.array[i], '-'))
		{
			j = remove_var(cmd->argv.array[i], msh->env);
			msh->env[j] = NULL;
			++i;
		}
	}
	--(msh->envused);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh *msh;
	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	msh->envspc = env_size(envp);
	msh->envused = msh->envspc;

	msh_unset(argc, argv, msh);
	print_2d_arr(msh->env);
}