/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/11 16:18:51 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <fcntl.h>
#include <unistd.h>

static int	exp_print_env(int fd, t_env *env);

int	msh_export(t_cmd *cmd, t_msh *msh)
{
	int	i;
	int	status;

	if (cmd->argc == 1)
		exp_print_env(cmd->io[1], &msh->env);
	status = 0;
	i = 1;
	while (cmd->argv.array[i])
	{
		if (ft_strncmp(cmd->argv.array[i], "_", 2))
		{
			if (env_set_entry(&msh->env, cmd->argv.array[i]) == MSH_INVVARID)
			{
				ft_dprintf(STDERR_FILENO, "msh: export: `%s': not a valid "
					"identifier\n", cmd->argv.array[i]);
				status = 1;
			}
		}
		++i;
	}
	return (status);
}

static int	exp_print_env(int fd, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (env->envp[i])
	{
		ft_dprintf(fd, "declare -x ");
		j = 0;
		while (env->envp[i][j])
		{
			if (env->envp[i][j] == '=')
				break ;
			++j;
		}
		ft_dprintf(fd, "\"%s\"\n", env->envp[i]);
		++i;
	}
	return (0);
}
