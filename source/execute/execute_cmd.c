/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/21 16:55:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdio.h"
#include "ft_string.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void				launch(t_cmd *cmd, t_msh *msh);
static t_builtinf		get_builtin(char const *cmd);
static inline t_errno			fd_set_standard(t_cmd *cmd);

/* Execute `cmd` */
t_errno	execute_cmd(t_cmd *cmd, t_msh *msh)
{
	t_builtinf const	builtin = get_builtin(cmd->argv.array[0]);
	int					wstatus;

	if (builtin)
		return (builtin(cmd, msh));
	msh->g_msh->child = fork();
	if (msh->g_msh->child == -1)
		return (perror("msh/execute"), MSH_FORKFAIL);
	if (msh->g_msh->child == 0)
		launch(cmd, msh);
	waitpid(msh->g_msh->child, &wstatus, 0);
	if (WIFEXITED(wstatus))
		msh->g_msh->exit = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		msh->g_msh->exit = WTERMSIG(wstatus) + 128;
	msh->g_msh->child = 0;
	return (MSH_SUCCESS);
}

/* Execute `cmd` or exit on failure. */
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
		perror("msh");
	msh_deinit(msh);
	exit(EXIT_FAILURE);
}

/* Check whether the `cmd` string matches the name of a builtin utility.
 * @return: A pointer to the utility function if found, or NULL otherwise. 
 */
static t_builtinf	get_builtin(char const *cmd)
{
	t_builtinf const	builtins[N_BUILTIN] = {
		msh_cd, msh_echo, msh_env, msh_exit, msh_pwd, msh_unset};
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
