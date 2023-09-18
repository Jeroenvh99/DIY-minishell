/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/18 14:50:26 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdio.h"
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	child(t_cmd *cmd, t_msh *msh);
static int	stddup(t_fd iofd[N_IO]);

/** 
 * @brief	Execute the binary specified by `cmd` and close all nonstandard
			file descriptors associated with it.
 * @return	An exit status:
 * 			MSH_SUCCESS		Success.
 * 			MSH_FORKFAIL	The call to fork() failed.
 */
t_errno	execute_bin(t_cmd *cmd, t_msh *msh)
{
	msh->child = fork();
	if (msh->child == -1)
		return (msh_perror(0), MSH_FORKFAIL);
	if (msh->child == 0)
		child(cmd, msh);
	msh->exit = execute_wait(msh);
	return (MSH_SUCCESS);
}

/**
 * @brief	Find the utility specified by `cmd` and execute it.
 * @return	This function never returns.
 */
static void	child(t_cmd *cmd, t_msh *msh)
{
	char		pname[PATH_MAX];
	char *const	fname = cmd->argv.array[0];

	if (stddup(cmd->io) != 0)
		msh_perror(0);
	else if (get_pathname(pname, fname, env_search(&msh->env, "PATH")) == 0)
	{
		handler_set(SIGINT, SIG_DFL);
		handler_set(SIGQUIT, SIG_DFL);
		if (execve(pname, cmd->argv.array, msh->env.envp) == -1)
			msh_perror(0);
	}
	else
		ft_dprintf(STDERR_FILENO, "msh: %s: command not found\n", fname);
	msh_deinit(msh);
	exit(EXIT_FAILURE);
}

/**
 * @brief	Merge the file descriptors on `cmd` into the standard streams. The
			original descriptors are closed.
 * @return	An exit status:
 * 			0	Success.
 * 			1	A call to dup2() failed.
 */
static inline int	stddup(t_fd iofd[N_IO])
{
	t_fd	fd;

	fd = STDIN_FILENO;
	while (fd < N_IO)
	{
		if (iofd[fd] != fd)
		{
			if (dup2(iofd[fd], fd) == -1)
				return (1);
			close(iofd[fd]);
			iofd[fd] = fd;
		}
		fd++;
	}
	return (0);
}
