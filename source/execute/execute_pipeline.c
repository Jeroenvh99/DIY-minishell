/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 16:06:56 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/19 14:57:55 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static t_errno	execute_pipeline_subsh(t_list **pipeline, t_msh *msh);
static t_errno	pipeln_fork(t_cmd *cmd, pid_t *pid, t_fd pipefd[2], t_msh *msh);
static t_errno	pipeln_fork_last(t_cmd *cmd, pid_t *pid, t_fd infd, t_msh *msh);
static inline void	kill_subshs(pid_t *pidv, size_t n);

/**
 * @brief	Execute all commands in `pipeline`. If `pipeline` contains more
 * 			than one simple command, spawn a subshell for every command.
 * 			`pipeline` is consumed.
 * @return	An exit status.
 */
t_errno	execute_pipeline(t_list **pipeline, t_msh *msh)
{
	t_cmd		*cmd;
	t_errno		errno;

	if ((*pipeline)->next != NULL)
	{
		errno = execute_pipeline_subsh(pipeline, msh);
		if (errno == MSH_PIPEFAIL || errno == MSH_FORKFAIL)
			exit(EXIT_FAILURE);
	}
	else
	{
		while (*pipeline)
		{
			cmd = list_pop_ptr(pipeline);
			errno = execute_cmd(cmd, msh);
			cmd_free(cmd);
			if (errno != MSH_SUCCESS)
				return (list_clear(pipeline, (t_freef)cmd_free), errno);
		}
	}
	return (errno);
}

/**
 * @brief	Execute a multiple-command pipeline.
 * @note		
 */
static t_errno	execute_pipeline_subsh(t_list **pipeline, t_msh *msh)
{
	pid_t *const	pidv = malloc(sizeof(pid_t) * list_size(*pipeline));
	t_fd			pipefd[2];
	t_cmd			*cmd;
	t_errno			errno;
	size_t			i;

	if (!pidv)
		return (list_clear(pipeline, (t_freef)cmd_free), MSH_MEMFAIL);
	pipefd[PIPE_READ] = STDIN_FILENO;
	i = 0;
	while ((*pipeline)->next)
	{
		cmd = list_pop_ptr(pipeline);
		errno = pipeln_fork(cmd, &pidv[i++], pipefd, msh);
		cmd_free(cmd);
		if (errno == MSH_PIPEFAIL || errno == MSH_FORKFAIL)
			return (kill_subshs(pidv, i), free(pidv), errno);
	}
	cmd = list_pop_ptr(pipeline);
	errno = pipeln_fork_last(cmd, &pidv[i++], pipefd[PIPE_READ], msh);
	cmd_free(cmd);
	if (errno == MSH_PIPEFAIL || errno == MSH_FORKFAIL)
		return (kill_subshs(pidv, i), free(pidv), errno);
	msh->exit = execute_wait_pipeline(pidv, i, msh);
	return (free(pidv), MSH_SUCCESS);
}

static t_errno	pipeln_fork(t_cmd *cmd, pid_t *pid, t_fd pipefd[2], t_msh *msh)
{
	if (cmd->io[IO_IN] == STDIN_FILENO)
		cmd->io[IO_IN] = pipefd[PIPE_READ];
	else if (pipefd[PIPE_READ] != STDIN_FILENO)
		close(pipefd[PIPE_READ]);
	if (pipe(pipefd) != 0)
		return (msh_perror(0), MSH_PIPEFAIL);
	*pid = fork();
	if (*pid == -1)
		return (close(pipefd[PIPE_READ]), close(pipefd[PIPE_WRITE]),
			msh_perror(0), MSH_FORKFAIL);
	if (*pid == 0)
	{
		if (cmd->io[IO_OUT] == STDOUT_FILENO)
			cmd->io[IO_OUT] = pipefd[PIPE_WRITE];
		else
			close(pipefd[PIPE_WRITE]);
		if (pipefd[PIPE_READ] != STDIN_FILENO)
			close(pipefd[PIPE_READ]);
		execute_subsh(cmd, msh);
	}
	close(pipefd[PIPE_WRITE]);
	return (MSH_SUCCESS);
}

static t_errno	pipeln_fork_last(t_cmd *cmd, pid_t *pid, t_fd infd, t_msh *msh)
{
	if (cmd->io[IO_IN] == STDIN_FILENO)
		cmd->io[IO_IN] = infd;
	else
		close(infd);
	*pid = fork();
	if (*pid == -1)
		return (msh_perror(0), MSH_FORKFAIL);
	if (*pid == 0)
		execute_subsh(cmd, msh);
	close(infd);
	return (MSH_SUCCESS);
}

static inline void	kill_subshs(pid_t *pidv, size_t n)
{
	while (n--)
		kill(*pidv, SIGKILL);
}
