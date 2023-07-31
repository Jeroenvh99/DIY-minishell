/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/07 09:18:12 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void			launch(t_cmd *cmd, t_msh *msh);
static t_builtinf	get_builtin(char const *cmd)

t_errno	execute(t_list **pipeline, t_msh *msh)

t_errno	execute_cmd(t_cmd *cmd, t_msh *msh)
{
	t_builtinf const	builtin = get_builtin(cmd->argv.array[0]);
	int					wstatus;

	if (builtin)
		return (builtin(cmd->argc, cmd->argv.array, msh->env.envp)); // tenzij builtin in pijplin zit; dan moet er een subshell komen / fork()
	msh->g_msh->child = fork();
	if (msh->g_msh->child == -1)
		return (perror("msh/execute"), MSH_FORKFAIL);
	if (msh->g_msh->child == 0)
		launch(cmd, msh);
	waitpid(msh->g_msh->child, &wstatus);
	if (WIFEXITED(wstatus))
		msh->g_msh->exit = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		msh->g_msh->exit = WTERMSIG(wstatus) + 128;
	msh->g_msh->child = 0;
	return (EXIT_SUCCESS);
}

static void	launch(t_cmd *cmd, t_msh *msh)
{
}

		execve(path, msh->cmds->cmd->argv.array, msh->env.envp);
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

static t_builtinf	get_builtin(char const *cmd)
{
	t_builtinf const	builtins[N_BUILTIN] = {
		cd, echo, env, exit, pwd, unset};
	char const *const	names[N_BUILTIN] = {
		"cd", "echo", "env", "exit", "pwd", "unset"};
	size_t				i;

	i = 0;
	while (i < N_BUILTIN)
	{
		if (ft_strncmp(cmd, names[i], -1) == 0)
			return (builtins[i]);
		i++;
	}
	return (NULL);
}
