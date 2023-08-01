/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/01 14:49:40 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_error.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

enum e_cderrno {
	CD_SUCCESS = 0,
	CD_ERROR,
	CD_MAXARG,
	CD_NOHOME,
	CD_NOOLDPWD,
	N_CD_ERRNO,
};

static void	cd_strerror(int errno);
static char	*get_dstdir(t_cmd *cmd, t_msh *msh);
static int	get_path(char *buf, char const *cwd, char const *dir);

int	msh_cd(t_cmd *cmd, t_msh *msh)
{
	char const *const	dstdir = get_dstdir(cmd, msh);
	char *const			cwd = getcwd(NULL, 0);
	char				path[PATH_MAX];

	if (!cwd || !dstdir)
		return (free(cwd), 1);
	if (cmd->argc > 2)
		return (cd_strerror(CD_MAXARG), free(cwd), 1);
	if (get_path(path, cwd, dstdir) != 0)
		return (msh_perror(1, "cd"), 1);
	if (chdir(path) != 0)
		return (msh_perror(2, "cd", cmd->argv.array[1]), 1);
	if (env_update(&msh->env, "OLDPWD", cwd) > 1)
		return (msh_perror(1, "cd"), 1);
	if (env_update(&msh->env, "PWD", path) > 1)
		return (msh_perror(1, "cd"), 1);
	free(cwd);
	return (0);
}

static void	cd_strerror(int errno)
{
	char const *const	errstrs[N_CD_ERRNO] = {
		NULL,
		"Error"
		"Too many arguments",
		"HOME not set",
		"OLDPWD not set",
	};

	ft_dprintf(STDERR_FILENO, "msh: cd: %s\n", errstrs[errno]);
}

static int	get_path(char *buf, char const *cwd, char const *dir)
{
	buf[0] = '\0';
	if (*dir != '/')
	{
		ft_strlcat(buf, cwd, PATH_MAX);
		ft_strlcat(buf, "/", PATH_MAX);
	}
	return (ft_strlcat(buf, dir, PATH_MAX) > PATH_MAX);
}

static char	*get_dstdir(t_cmd *cmd, t_msh *msh)
{
	char	*dstdir;

	if (cmd->argc == 1 || ft_strncmp(cmd->argv.array[1], "--", 3) == 0)
	{
		dstdir = env_search(&msh->env, "HOME");
		if (!dstdir)
			cd_strerror(CD_NOHOME);
	}
	else if (ft_strncmp(cmd->argv.array[1], "-", 2) == 0)
	{
		dstdir = env_search(&msh->env, "OLDPWD");
		if (dstdir)
			printf("%s\n", dstdir);
		else
			cd_strerror(CD_NOOLDPWD);
	}
	else
		dstdir = cmd->argv.array[1];
	return (dstdir);
}
