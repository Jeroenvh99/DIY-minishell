/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/24 11:01:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_error.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static int	copy_str(const char *src, char *dst, int i, int n);
//static char	*ft_strjoin_dir(char const *s1, char const *s2);
//static char	*get_env_dir(char *name, t_cmd *cmd, t_msh *msh);
static char	*get_dstdir(t_cmd *cmd, t_msh *msh);
static int	get_path(char *buf, char const *cwd, char const *dir);

int	msh_cd(t_cmd *cmd, t_msh *msh)
{
	char *const	dstdir = get_dstdir(cmd, msh);
	char *const	cwd = getcwd(NULL, 0);
	char		path[PATH_MAX];

    if (!buf || !dstdir)
        return (free(cwd), 1);
	if (cmd->argc > 2)
	{
		ft_dprintf(2, "msh: cd: too many arguments\n"); //msh_strerror
		return (free(cwd), 1);
	}
	if (get_path(path, cwd, dstdir) != 0)
		return (msh_perror(1, "cd"), 1);
	if (chdir(path) != 0)
		return (msh_perror(2, "cd", cmd->argv.array[1]), 1);
	env_set(&msh->env, ft_strjoin("OLDPWD=", cwd));
	env_set(&msh->env, ft_strjoin("PWD=", path));
	free(cwd);
	return (0);
}
//DB: bash voegt OLDPWD en PWD niet toe als ze niet al bestaan

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

/*static int	copy_str(const char *src, char *dst, int i, int n)
{
	while (i < n)
	{
		dst[i] = *src;
		++i;
		++src;
	}
	return (i);
}

static char	*ft_strjoin_dir(char const *s1, char const *s2)
{
	char	*string;
	size_t	len1;
	size_t	len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (ft_strchr(s2, '/'))
		--len2;
	string = malloc((len1 + len2 + 2) * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = copy_str(s1, string, 0, len1);
	string[i] = '/';
	++i;
	len2 += len1 + 1;
	i = copy_str(s2, string, i, len2);
	string[i] = '\0';
	return (string);
}*/

static char	*get_env_dir(char *name, t_cmd *cmd, t_msh *msh)
{
	char *const	dstdir = env_search(&msh->env, name);

	if (dstdir == NULL)
		ft_dprintf(cmd->io[IO_ERR], "msh: cd: %s not set\n", name);
	return (dstdir);
}

static char	*get_dstdir(t_cmd *cmd, t_msh *msh)
{
	char	*dstdir;

	if (cmd->argc == 1)
		dstdir = get_env_dir("HOME", cmd, msh);
	else if (ft_strncmp(cmd->argv.array[1], "-", 2) == 0)
	{
		dstdir = get_env_dir("OLDPWD", cmd, msh);
		if (dstdir)
			ft_dprintf(cmd->io[IO_OUT], "%s\n", dstdir);
	}
	else if (ft_strncmp(cmd->argv.array[1], "--", 3) == 0)
		dstdir = get_env_dir("HOME", cmd, msh);
	else
		dstdir = cmd->argv.array[1];
	return (dstdir);
}
