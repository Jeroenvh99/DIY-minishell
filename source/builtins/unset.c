/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:50:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/18 16:46:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <stdlib.h>

int	msh_unset(t_cmd *cmd, t_msh *msh)
{
	int	i;

	i = 1;
    while (ft_strchr(cmd->argv.array[i], '-'))
    {
        ft_dprintf(cmd->io[IO_ERR], "msh: unset: %s: not a valid identifier", cmd->argv.array[i]);
        ++i;
    }
	while (cmd->argv.array[i])
	{
		if (!ft_strchr(cmd->argv.array[i], '_'))
			env_unset(&msh->env, cmd->argv.array[i]);
		++i;
	}
	return (0);
}
