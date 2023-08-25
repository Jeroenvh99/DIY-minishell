/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:45:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/25 13:27:15 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

#include "ft_ctype.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include <stdio.h>
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
	int	status;

	if (cmd->argc > 2)
		return (exit_strerror(EXIT_INVARG), 1);
	printf("exit\n");
	if (cmd->argc == 2)
		status = get_status(cmd->argv.array[1]);
	else
		status = 0;
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
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(STDERR_FILENO, "msh: exit: %s: numeric argument "
				"required\n", str);
			return (2);
		}
		++i;
	}
	return (ft_atoi(str));
}
