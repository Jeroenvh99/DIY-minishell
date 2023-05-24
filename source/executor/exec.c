/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/23 17:44:56 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	exec(t_msh *msh)
{
	int		*status;
	pid_t	pid;

	else
	{
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
		execve(state->comm_paths[state->index], cmd->argv,
			msh->env);
	exit(errno);
}

static void	parent_end(t_info *state, int child_id, int *tube)
{
	int	status;

	if (close(tube[0]) == -1)
	{
		msh->last_status = ;
		return -1;
	}
	waitpid(child_id, &status, 0);
	if (WIFEXITED(status))
		msh->last_status = status;
}

int	exec_command(char **envp, int fd, t_info *state)
{
	pid_t	pid;

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