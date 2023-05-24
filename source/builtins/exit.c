/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/23 15:05:59 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../include/minishell.h"
#include "./../../lib/libft/include/ft_ctype.h"
#include "./../../lib/libft/include/ft_stdlib.h"
#include <stdlib.h>
#include <unistd.h>

int	check_arg(char *str, int errfd)
{
	while (*str)
	{
		if (ft_isalpha(*str))
		{
			write(errfd, "exit\n", 5);
			ft_dprintf(errfd, "msh: %s: exit: numeric argument required", str);
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
		write(cmd->io->err, "exit\n", 5);
		ft_dprintf(cmd->io->err, "msh: exit: too many arguments");
		return (1);
	}
	else if (cmd->argc == 2)
	{
		if (check_arg(cmd->argv.array[1], cmd->io->err))
			status = ft_atoi(cmd->argv.array[1]);
	}
	msh_deinit(msh);
	exit(status);
}

int	main(int argc, char **argv)
{
	msh_exit(argc, argv);
}
