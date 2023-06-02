/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/02 11:29:15 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "msh.h"
#include <unistd.h>

int	getbuiltin(char *cmd)
{
	if (ft_strnstr(cmd, "cd", 3))
		return (0);
	if (ft_strnstr(cmd, "echo", 5))
		return (1);
	if (ft_strnstr(cmd, "env", 4))
		return (2);
	if (ft_strnstr(cmd, "exit", 5))
		return (3);
	if (ft_strnstr(cmd, "pwd", 4))
		return (4);
	if (ft_strnstr(cmd, "unset", 6))
		return (5);
	return (-1);
}

int	exec(t_msh *msh)
{
	int		*status;
	pid_t	pid;
	int		bi;
	const int	(*builtins[6])(t_cmd * cmd, t_msh * msh) = { cd, echo, env, exit, pwd, unset };

	while (msh->cmds)
	{
		bi = getbuiltin(msh->cmds->cmd->argv.array[0]) if (bi > -1)
		{
			msh->status = builtins[bi](msh->cmds->cmd, msh);
		}
		else
		{
			execve(path, msh->cmds->cmd->argv.array, msh->env);
		}
	}
	return (0);
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
		msh->last_status = status;
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