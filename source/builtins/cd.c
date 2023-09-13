/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/13 00:07:42 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_error.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

enum e_cderrno {
	CD_SUCCESS = 0,
	CD_ERROR,
	CD_INVARGN,
	CD_INVOPT,
	CD_NOHOME,
	CD_NOOLDPWD,
	CD_ERANGE,
	N_CD_ERRNO,
};

static int	path_absolute(char *path, char const *arg, t_msh *msh);
static int	path_relative(char *path, char const *arg, t_msh *msh);
static int	path_env(char *path, char const *arg, t_fd outf, t_msh *msh);
static void	cd_strerror(int errno);

int	msh_cd(t_cmd *cmd, t_msh *msh)
{
	char	path[PATH_MAX];

	if (cmd->argc > 2)
		return (cd_strerror(CD_INVARGN), 1);
	if (cmd->argv.array[1][0] == '/')
		path_absolute(path, cmd->argv.array[1], msh);
	else if (cmd->argv.array[1][0] == '-')
		path_env(path, cmd->argv.array[1], cmd->io[1], msh);
	else
		path_relative(path, cmd->argv.array, msh);
}

static int	path_absolute(char *path, char const *arg, t_msh *msh)
{
	(void) msh;
	if (ft_strncpy(path, arg, PATH_MAX) > PATH_MAX - 1)
		return (CD_ERANGE);
	return (CD_SUCCESS);
}

static int	path_env(char *path, char const *arg, t_fd outf, t_msh *msh)
{
	char const	*envval;

	if (cmd->argc == 1 || ft_strncmp(arg, "--", 3) == 0)
	{
		envval = env_search(&msh->env, "HOME");
		if (!envval)
			return (CD_NOHOME);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		envval = env_search(&msh->env, "OLDPWD");
		if (envval)
			ft_dprintf(outf, "%s\n", dstdir);
		else
			return (CD_NOOLDPWD);
	}
	else
		return (ft_dprintf(2, "msh: cd: %s: invalid option", arg), CD_ERROR);
	if (envval && ft_strncpy(path, envval, PATH_MAX) > PATH_MAX - 1)
		return (CD_ERANGE);
	return (CD_SUCCESS);
}

static int	path_relative(char *path, char const *arg, t_msh *msh)
{
	ft_strlcpy(path, msh->cwd.b, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	if (ft_strlcat(path, arg, PATH_MAX) > PATH_MAX - 1)
		return (CD_ERANGE);
	return (CD_SUCCESS);
}

static int	cd_common(t_msh *msh, char const *path)
{
	if (chdir(path) != 0)
		return (msh_perror(2, "cd", cmd->argv.array[1]), 1);
	if (env_update(&msh->env, "OLDPWD", msh->cwd.b) > 1)
		return (msh_perror(1, "cd"), 1);
	if (env_update(&msh->env, "PWD", path) > 1)
		return (msh_perror(1, "cd"), 1);
	if (cwd_update(&msh->cwd) == MSH_GENERIC)
		return (msh_perror(1, "cd"), 1);
}

static char const *const	g_errstrs[N_CD_ERRNO] = {
	"",
	"Error",
	"Too many arguments",
	"Invalid option",
	"HOME not set",
	"OLDPWD not set",
	"Pathname too long",
};

static void	cd_strerror(int errno)
{
	ft_dprintf(STDERR_FILENO, "msh: cd: %s\n", g_errstrs[errno]);
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
