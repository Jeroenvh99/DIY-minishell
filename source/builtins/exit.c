/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/26 15:50:39 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include "msh.h"
#include <stdlib.h>
#include <unistd.h>

int	check_arg(char *str, int errfd)
{
	while (*str)
	{
		if (ft_isalpha(*str))
		{
			ft_dprintf(errfd, "exit\nmsh: %s: exit: numeric argument required\n", str);
			return (0);
		}
		++str;
	}
	return (1);
}

int	msh_exit(t_cmd *cmd, t_msh *msh)
{
	int	status;

	status = 0;
	if (cmd->argc > 2)
	{
		ft_dprintf(cmd->io.err, "exit\nmsh: exit: too many arguments\n");
		return (1);
	}
	else if (cmd->argc == 2)
	{
		if (check_arg(cmd->argv.array[1], cmd->io.err))
			status = ft_atoi(cmd->argv.array[1]);
		else
			status = 255;
	}
	msh_deinit(msh);
	exit(status);
}
