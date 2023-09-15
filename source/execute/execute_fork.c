/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_fork.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/05 12:41:26 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdio.h"
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	child(t_cmd *cmd, t_msh *msh);
static int	fd_set_standard(t_cmd *cmd);

/** 
 * @brief	Execute the binary specified by `msh`.
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
	if (cmd->io[IO_IN] > 0)
		close(cmd->io[IO_IN]);
	if (cmd->io[IO_OUT] > 1)
		close(cmd->io[IO_OUT]);
	msh->exit = execute_wait(msh);
	return (MSH_SUCCESS);
}

/**
 * @brief	Execute a command inside a subshell.
 * @return	This function never returns.
 */
void	execute_subsh(t_cmd *cmd, t_msh *msh)
{
	if (fd_set_standard(cmd) == 0)
	{
		execute_cmd(cmd, msh);
	}
	else
	{
		msh->exit = EXIT_FAILURE;
		msh_perror(0);
	}
	cmd_free(cmd);
	msh_deinit(msh);
	exit(msh->exit);
}

/**
 * @brief	Wait for the child process.
 * @return	The child's exit status or, if the child was terminated by way of a
 * 			signal: the signal number incremented by 128.
 */
int	execute_wait(t_msh *msh)
{
	int	wstatus;

	waitpid(msh->child, &wstatus, 0);
	msh->child = 0;
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	return (WEXITSTATUS(wstatus));
}

/**
 * @brief	Find the utility specified by `cmd` and execute it.
 * @return	This function never returns.
 */
static void	child(t_cmd *cmd, t_msh *msh)
{
	char		pname[PATH_MAX];
	char *const	fname = cmd->argv.array[0];

	if (fd_set_standard(cmd) == 0)
	{
		if (get_pathname(pname, fname, env_search(&msh->env, "PATH")) == 0)
			execve(pname, cmd->argv.array, msh->env.envp);
		ft_dprintf(STDERR_FILENO, "msh: %s: command not found\n", fname);
	}
	else
		msh_perror(0);
	msh_deinit(msh);
	exit(EXIT_FAILURE);
}

/**
 * @brief	Merge the file descriptors on `cmd` into the standard streams.
 * @return	An exit status:
 * 			0	Success.
 * 			1	A call to dup2() failed.
 */
static inline int	fd_set_standard(t_cmd *cmd)
{
	t_fd	fd;

	fd = STDIN_FILENO;
	while (fd < N_IO)
	{
		if (cmd->io[fd] != fd)
		{
			if (dup2(cmd->io[fd], fd) == -1)
				return (1);
			close(cmd->io[fd]);
			cmd->io[fd] = fd;
		}
		fd++;
	}
	return (0);
}
