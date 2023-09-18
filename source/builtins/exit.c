/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/18 14:01:52 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include <stdlib.h>
#include <unistd.h>

enum e_exiterrno {
	EXIT_SUCCESS_ = 0,
	EXIT_INVARG,
	N_EXIT_ERRNO,
};

static void	exit_strerror(int errno);
static int	get_status(char const *str);

/**
 * @brief	Exit the shell.
 * @return	Never returns, or returns 1 on error.
 */
int	msh_exit(t_cmd *cmd, t_msh *msh)
{
	int		status;
	size_t	i;

	status = 0;
	ft_dprintf(cmd->io[1], "exit\n");
	i = 1;
	while (i < cmd->argc)
	{
		status = get_status(cmd->argv.array[i]);
		if (i == 1 && status == 2)
		{
			ft_dprintf(STDERR_FILENO, "msh: exit: %s: numeric argument "
				"required\n", cmd->argv.array[i]);
			break ;
		}
		if (i > 1)
			return (exit_strerror(EXIT_INVARG), 1);
		++i;
	}
	msh_deinit(msh);
	exit(status);
	return (1);
}

static void	exit_strerror(int errno)
{
	char const *const	errmsg[N_EXIT_ERRNO] = {
		NULL,
		"Too many arguments"};

	ft_dprintf(STDERR_FILENO, "msh: exit: %s\n", errmsg[errno]);
}

static int	get_status(char const *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		++i;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (2);
		}
		++i;
	}
	return ((unsigned char)ft_atoi(str));
}
