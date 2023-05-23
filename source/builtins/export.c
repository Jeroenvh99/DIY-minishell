/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/23 14:27:50 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_stdio.h"
#include <fcntl.h>
#include <unistd.h>

int	exp_print_env(t_msh *msh, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (msh->env[i])
	{
		if (write(cmd->io->out, "declare -x ", 11) == -1)
			return (-1);
		j = 0;
		while (msh->env[i][j])
		{
			if (msh->env[i][j] == '=')
				break ;
			++j;
		}
		if (write(cmd->io->out, msh->env[i], j + 1) == 0)
			return (-1);
		ft_dprintf(cmd->io->out, "\"%s\"\n", msh->env[i] + j + 1);
		++i;
	}
	return (0);
}

int	realloc_env(t_msh *msh, int extra_size)
{
	int		i;
	char	**new_env;

	msh->envspc += extra_size;
	i = msh->envspc;
	new_env = (char **)malloc(i * sizeof(char *));
	if (!new_env)
		return (-1);
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
	return (0);
}

int	msh_export(t_cmd *cmd, t_msh *msh)
{
	int		i;
	int		j;
	char	*var;

	if (cmd->argc == 0)
	{
		if (exp_print_env(msh, cmd) == -1)
			return (-1);
	}
	i = 1;
	while (cmd->argv.array[i])
	{
		if (ft_strchr(cmd->argv.array[i], '-'))
			return (0); // invalid option
		if (ft_strchr(cmd->argv.array[i], '='))
		{
			// check if the name already exists in env and update if necessary
			if (msh->envused == msh->envspc)
			{
				if (realloc_env(msh, cmd->argc - 1 - i) == -1)
					return (-1);
			}
			var = ft_strdup(cmd->argv.array[i]);
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