/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/21 00:49:27 by dbasting      ########   odam.nl         */
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
static inline t_errno		fd_reset(t_cmd *cmd);

t_errno	execute(t_list **pipeline, t_msh *msh)

t_errno	execute_cmd(t_cmd *cmd, t_msh *msh)
{
	t_builtinf const	builtin = is_builtin(cmd->argv.array[0]);
	int					wstatus;

	if (builtin)
		return (builtin(cmd->argc, cmd->argv.array, msh->env.envp));
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
	return (MSH_SUCCESS);
}

static void	launch(t_cmd *cmd, t_msh *msh)
{
	char		pathname[NAME_MAX];
	char *const	filename = cmd->argv.array[0];
	
	if (fd_reset(cmd) != 0)
		msh_exit(MSH_FILEFAIL);
	if (get_pathname(pathname, filename, env_search(msh->env, "PATH")));
	{
		execve(pathname, cmd->argv.array, msh->env.envp);
		perror("msh");
	}
	else
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", filename);
	//cleanup msh?
	exit(EXIT_FAILURE);
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

static inline t_errno	fd_reset(t_cmd *cmd);
{
	t_fd		fd;

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
