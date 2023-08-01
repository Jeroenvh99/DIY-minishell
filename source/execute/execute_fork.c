/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_fork.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/28 16:39:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdio.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void		launch(t_cmd *cmd, t_msh *msh);
static int		fork_wait(t_msh *msh);
static t_errno	fd_set_standard(t_cmd *cmd);

/* Execute `builtin`, creating a subshell if necessary. */
t_errno	execute_builtin(t_builtinf const builtin, t_cmd *cmd, t_msh *msh)
{
	if (cmd->subsh == 0)
	{
		msh->g_msh->exit = builtin(cmd, msh);
		return (MSH_SUCCESS);
	}
	msh->g_msh->child = fork();
	if (msh->g_msh->child == -1)
		return (msh_perror(0), MSH_FORKFAIL);
	if (msh->g_msh->child == 0)
		exit(builtin(cmd, msh));
	msh->g_msh->exit = fork_wait(msh);
	return (MSH_SUCCESS);
}

/* Execute `cmd`. */
t_errno	execute_bin(t_cmd *cmd, t_msh *msh)
{
	msh->g_msh->child = fork();
	if (msh->g_msh->child == -1)
		return (msh_perror(0), MSH_FORKFAIL);
	if (msh->g_msh->child == 0)
		launch(cmd, msh);
	msh->g_msh->exit = fork_wait(msh);
	return (MSH_SUCCESS);
}

/* Wait for the child process. Return the child's exit status. */
static int	fork_wait(t_msh *msh)
{
	int	wstatus;
	int	exit;

	waitpid(msh->g_msh->child, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		exit = WTERMSIG(wstatus) + 128;
	msh->g_msh->child = 0;
	return (exit);
}

/* Find the utility specified by `cmd` and execute it, or exit on failure. */
static void	launch(t_cmd *cmd, t_msh *msh)
{
	char		pname[PATH_MAX];
	char *const	fname = cmd->argv.array[0];

	if (fd_set_standard(cmd) != 0)
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

/* Merge the file descriptors on `cmd` with the standard streams. */
static inline t_errno	fd_set_standard(t_cmd *cmd)
{
	t_fd	fd;

	fd = STDIN_FILENO;
	while (fd < N_IO)
	{
		if (dup2(cmd->io[fd], fd) != 0)
			return (1);
		close(cmd->io[fd]);
		cmd->io[fd] = -1;
		fd++;
	}
	return (0);
}