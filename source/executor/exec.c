/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/19 18:08:44 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "msh.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

t_errno	execute(t_list **pipeline, t_msh *msh)

int	execute_cmd(t_cmd *cmd, t_msh *msh)
{
	t_builtinf const	builtin = is_builtin(cmd->argv.array[0]);
	int					wstatus;
	pid_t				pid;

	if (builtin)
		return (builtin(cmd->argc, cmd->argv.array, msh->env.envp)); // tenzij builtin in pijplin zit; dan moet er een subshell komen / fork()
	pid = fork();
	if (pid == -1)
		return (perror("msh:"), MSH_FORKFAIL);
	if (pid == 0)
		execve(path, msh->cmds->cmd->argv.array, msh->env.envp);
	waitpid(pid, &wstatus);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (EXIT_SUCCESS);
}

static void	child_process(int *tube, char **envp, int fd, t_info *state)
{
	if (dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
		exit(errno);
	if (dup2(tube[1], STDOUT_FILENO) == -1 || close(tube[1]) == -1
		|| close(tube[0]) == -1)
		exit(errno);
	state->comm_paths[state->index] = get_path(state->paths,
												state->comm_argv[state->index][0]);
	if (builtin)
		i = builtin()
			exit(i);
	else
		execve(state->comm_paths[state->index], cmd->argv, msh->env);
	exit(errno);
}

static void	parent_end(t_info *state, int child_id, int *tube)
{
	int	status;

	if (close(tube[0]) == -1)
	{
		msh->last_status = ;
		return (-1);
	}
	waitpid(child_id, &status, 0);
	if (WIFEXITED(status))
		msh->last_status = WEXITSTATUS(status);
}

int	exec_command(char **envp, int fd, t_info *state)
{
	pid_t pid;

	pid = fork_if_necessary(tube);
	if (pid == 0)
	{
		if (builtin)
			child_process_builtin(tube, envp, fd);
		else
			child_process(tube, envp, fd);
	}
	else if (cmd->next)
	{
		if (close(tube[1]) == -1)
		{
			exit(EXIT_FAILURE);
		}
		exec_command(envp, tube[0], state);
	}
	parent_end(state, pid, tube);
}
