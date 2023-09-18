/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/15 13:38:48 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_error.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <limits.h>
#include <stdlib.h>

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
	int		stat;

	if (cmd->argc > 2)
		return (cd_strerror(CD_INVARGN), 1);
	if (cmd->argv.array[1][0] == '/')
		stat = path_absolute(path, cmd->argv.array[1], msh);
	else if (cmd->argv.array[1][0] == '-')
		stat = path_env(path, cmd->argv.array[1], cmd->io[1], msh);
	else
		stat = path_relative(path, cmd->argv.array, msh);
	if (stat != CD_SUCCESS)
		return (cd_strerror(stat), 1);
	if (cd_chdir)
		msh_perror(2, "cd", cmd->argv.array[1]);
	if (env_update(&msh->env, "OLDPWD", msh->cwd.b) > 1
		|| env_update(&msh->env, "PWD", path) > 1
		|| cwd_update(&msh->cwd, path) == MSH_GENERIC)
		return (msh_perror(1, "cd"), 1);
}

/**
 * @brief	Copy the absolute path held in `arg` to `path`.
 * @return	An exit status. Possible values:
 * 			CD_SUCCESS	Success.
 * 			CD_ERANGE	The string `arg` contained more than PATH_MAX - 1
 * 						characters.
 */
static int	path_absolute(char *path, char const *arg, t_msh *msh)
{
	(void) msh;
	if (ft_strlcpy(path, arg, PATH_MAX) > PATH_MAX - 1)
		return (CD_ERANGE);
	return (CD_SUCCESS);
}

/**
 * @brief	Copy a path from the environment to `path`.
 * @return	An exit status. Possible values:
 * 			CD_SUCCESS	Success.
 * 			CD_NOHOME	The variable HOME was not set while `arg` held '--'.
 * 			CD_NOOLDPWD	The variable OLDPWD was not set while `arg` held '-'.
 * 			CD_ERANGE	The variable contained more than PATH_MAX - 1
 * 						characters.
 */
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
	if (envval && ft_strlcpy(path, envval, PATH_MAX) > PATH_MAX - 1)
		return (CD_ERANGE);
	return (CD_SUCCESS);
}

/**
 * @brief	Resolve a relative path by concatenating the shell's cwd variable
 * 			and `arg` in `path`.
 * @return	An exit status. Possible values:
 * 			CD_SUCCESS	Success.
 * 			CD_ERANGE	The combined path would contain more than PATH_MAX - 1
 * 						characters.
 */
static int	path_relative(char *path, char const *arg, t_msh *msh)
{
	ft_strlcpy(path, msh->cwd.b, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	if (ft_strlcat(path, arg, PATH_MAX) > PATH_MAX - 1)
		return (CD_ERANGE);
	return (CD_SUCCESS);
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
