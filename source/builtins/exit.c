/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/18 17:03:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include "msh.h"
#include "msh_utils.h"
#include <stdlib.h>
#include <unistd.h>

int	check_arg(char *str, int errfd)
{
    int i;

    i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(errfd, "msh: %s: exit: numeric argument required\n", str);
			return (0);
		}
		++i;
	}
	return (1);
}

int	msh_exit(t_cmd *cmd, t_msh *msh)
{
	int	status;

	status = 0;
	if (cmd->argc > 2)
	{
		ft_dprintf(cmd->io[IO_ERR], "msh: exit: too many arguments\n");
		return (1);
	}
	ft_dprintf(cmd->io[IO_OUT], "exit\n");
	if (cmd->argc == 2)
	{
		if (check_arg(cmd->argv.array[1], cmd->io[IO_ERR]))
			status = ft_atoi(cmd->argv.array[1]);
		else
			status = 255;
	}
	msh_deinit(msh);
	exit(status);
    return (0);
}
