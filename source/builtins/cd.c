/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/18 12:59:19 by dbasting         ###   ########.fr       */
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
	CD_MAXARG,
	CD_NOHOME,
	CD_NOOLDPWD,
	N_CD_ERRNO,
};

static void	cd_strerror(int errno);
static char	*arg_get(t_cmd *cmd, t_msh *msh);
static int	get_path(char *buf, char const *cwd, char const *dir);
static void canonicalise(char *str);

int	msh_cd(t_cmd *cmd, t_msh *msh)
{
	char const *const	arg = arg_get(cmd, msh); // stap 1 en 2
	char				*path;

	if (!arg) 
		return (1);
	if (cmd->argc > 2)
		return (cd_strerror(CD_MAXARG), 1);
	path = path_get(arg, msh->cwd);
	if (!path)
		return (msh_perror(1, "cd"), 1);
	canonicalise(path); // stap 8
	if (chdir(path) != 0) // stap 10
		return (msh_perror(2, "cd", cmd->argv.array[1]), 1);
	ft_strlcpy(msh->cwd, path, PATH_MAX);
	if (env_update(&msh->env, "OLDPWD", cwd) > 1) // beide updates samen wrappen! zie 
		return (msh_perror(1, "cd"), 1);
	if (env_update(&msh->env, "PWD", path) > 1)
		return (msh_perror(1, "cd"), 1);
	free(path);
	return (0);
}

static void removeprevdir(char *str, size_t i, size_t j)
{
    if (i < 0)
        return ;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		--i;
        if (i == 0)
            return ;
	}
    ++i;
	while (str[j])
    {
        str[i] = str[j];
        ++i;
        ++j;
    }
    str[i] = '\0';
}

static void removecurdir(char *str, size_t i)
{
    size_t  j;
    int     curdir;

    curdir = 0;
    j = i + 1;
    while (str[i])
    {
        if (curdir == 0 && str[i] == '/')
            ++j;
        else
            curdir = 1;
        str[i] = str[j];
        ++i;
        ++j;
    }
    str[i] = '\0';
}

static void canonicalise(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
            if (str[i + 1] && str[i + 2] && str[i + 1] == '.' && str[i + 2] == '/')
            {
                removeprevdir(str, i - 2, i + 3);
            }
            else
            {
                removecurdir(str, i - 1);
                i -= 2;
            }
		}
		++i;
	}
}

static void	cd_strerror(int errno)
{
	char const *const	errstrs[N_CD_ERRNO] = {
		NULL,
		"Error",
		"Too many arguments",
		"HOME not set",
		"OLDPWD not set",
	};

	ft_dprintf(STDERR_FILENO, "msh: cd: %s\n", errstrs[errno]);
}

static char	*path_get(char const *arg, char const *cwd)
{
	char	*path;
	size_t	size;

	if (arg[0] == '/') // stap 3
		return (ft_strdup(arg));
	size = ft_strlen(cwd) + 1 + ft_strlen(arg) + 1;
	path = malloc(size * sizeof(char)); // stap 7
	if (!path)
		return (NULL);
	ft_strlcat(path, cwd, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, arg, PATH_MAX);
	return (path);
}

static char	*arg_get(t_cmd *cmd, t_msh *msh)
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
