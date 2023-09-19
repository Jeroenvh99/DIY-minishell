/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/18 15:06:36 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

enum e_cderrno {
	CD_SUCCESS = 0,
	CD_ERROR,
	CD_MAXARG,
	CD_NOHOME,
	CD_NOOLDPWD,
	N_CD_ERRNO,
};

static void			cd_strerror(int errno);
static char	const	*arg_get(t_cmd *cmd, t_msh *msh);
static char			*path_get(char const *arg, char const *cwd);

int	msh_cd(t_cmd *cmd, t_msh *msh)
{
	char const *const	arg = arg_get(cmd, msh);
	char				*path;

	if (!arg)
		return (1);
	if (cmd->argc > 2)
		return (cd_strerror(CD_MAXARG), 1);
	path = path_get(arg, msh->cwd);
	if (!path)
		return (msh_perror(1, "cd"), 1);
	if (ft_strncmp(arg, "..", 2) == 0 || ft_strncmp(arg, "../", 3) == 0)
		ft_strlcpy(msh->cwd, path, PATH_MAX);
	path_canonicalize(path);
	if (chdir(path) != 0)
		return (msh_perror(2, "cd", arg), 1);
	ft_strlcpy(msh->cwd, path, PATH_MAX);
	if (env_update(&msh->env, "OLDPWD", env_search(&msh->env, "PWD")) > 1)
		return (msh_perror(1, "cd"), 1);
	if (env_update(&msh->env, "PWD", path) > 1)
		return (msh_perror(1, "cd"), 1);
	free(path);
	return (0);
}

void	path_canonicalize(char *str)
{
	size_t	i;

	removeduplicateslash(str);
	if (str[1] != '\0')
		removelastslash(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (str[i + 1] && str[i + 1] == '.')
				i -= removeprevdir(str, i - 2);
			else
				i -= removecurdir(str, i);
		}
		else
			++i;
	}
	if (str[1] != '\0')
		removelastslash(str);
}

static char const *const	g_errstrs[N_CD_ERRNO] = {
	"", "Error", "Too many arguments", "HOME not set", "OLDPWD not set"};

static void	cd_strerror(int errno)
{
	ft_dprintf(STDERR_FILENO, "msh: cd: %s\n", g_errstrs[errno]);
}

static char const	*arg_get(t_cmd *cmd, t_msh *msh)
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
			ft_dprintf(cmd->io[1], "%s\n", dstdir);
		else
			cd_strerror(CD_NOOLDPWD);
	}
	else
		dstdir = cmd->argv.array[1];
	return (dstdir);
}

static char	*path_get(char const *arg, char const *cwd)
{
	char	*path;
	size_t	size;

	if (arg[0] == '/')
		return (ft_strdup(arg));
	size = ft_strlen(cwd) + 1 + ft_strlen(arg) + 1;
	path = malloc(size * sizeof(char));
	if (!path)
		return (NULL);
	ft_strlcpy(path, cwd, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, arg, PATH_MAX);
	return (path);
}
