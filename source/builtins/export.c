/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/25 18:22:28 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
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
		if (write(cmd->io->out, msh->env[i], j + 1) == -1)
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

	msh->env.len += extra_size;
	i = msh->env.len;
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

int	env_empty_loc(t_msh *msh)
{
	int	j;

	j = 0;
	while (msh->env[j] && j <= msh->used)
		++j;
	return (j);
}

void	write_new_var(t_cmd *cmd, t_msh *msh, int i)
{
	int		j;
	char	*var;

	// check if the name already exists in env and update if necessary
	j = get_var_index(cmd->argv.array[i], msh->env);
	if (j)
	{
		var = ft_strjoin(msh->env[j], ft_strchr(cmd->argv.array[i], '=') + 1);
		free(msh->env[j]);
	}
	else
	{
		j = env_empty_loc(msh);
		var = ft_strdup(cmd->argv.array[i]);
	}
	msh->env[j] = var;
	++(msh->env.used);
}

int	msh_export(t_cmd *cmd, t_msh *msh)
{
	int	i;

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
			if (msh->env.used == msh->env.len)
			{
				if (realloc_env(msh, cmd->argc - 1 - i) == -1)
					return (-1);
			}
			write_new_var(cmd, msh, i);
		}
		++i;
	}
	return (0);
}
