/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:50:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/26 16:59:39 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <stdlib.h>

int	msh_unset(t_cmd *cmd, t_msh *msh)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->argv.array[i])
	{
		if (!ft_strchr(cmd->argv.array[i], '-'))
		{
			j = remove_var(cmd->argv.array[i], msh->env.envp);
			if (j > -1)
			{
				msh->env.envp[j] = NULL;
				--(msh->env.used);
			}
		}
		++i;
	}
	return (0);
}
