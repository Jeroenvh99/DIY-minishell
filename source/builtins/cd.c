/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/25 18:11:16 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdio.h"
#include "msh.h"
#include <stdlib.h>
#include <unistd.h>

int	copy_str(const char *src, char *dst, int i, int n)
{
	while (i < n)
	{
		dst[i] = *src;
		++i;
		++src;
	}
	return (i);
}

char	*ft_strjoin_dir(char const *s1, char const *s2)
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
}

char	*get_env_dir(char *name, t_cmd *cmd, t_msh *msh)
{
	char	*dstdir;

	dstdir = env_search(&msh->env, name);
	if (!dstdir)
	{
		ft_dprintf(cmd->io.err, "msh: cd: %s not set", name);
		return (NULL);
	}
	return (dstdir);
}

char	*get_dstdir(t_cmd *cmd, t_msh *msh)
{
	char	*dstdir;

	dstdir = NULL;
	if (cmd->argc == 1)
	{
		dstdir = get_env_dir("HOME", cmd, msh);
	}
	else
	{
		if (ft_strncmp(cmd->argv.array[1], "-", 2) == 0)
		{
			dstdir = get_env_dir("OLDPWD", cmd, msh);
            if (dstdir)
			    ft_dprintf(cmd->io.out, "%s\n", dstdir);
		}
        else if (ft_strncmp(cmd->argv.array[1], "--", 3) == 0)
        {
            dstdir = get_env_dir("HOME", cmd, msh);
        }
		else
			dstdir = cmd->argv.array[1];
	}
	return (dstdir);
}

int	msh_cd(t_cmd *cmd, t_msh *msh)
{
	char	*dstdir;
	char	*newdir;
	char	*buf;

    buf = NULL;
	dstdir = get_dstdir(cmd, msh);
    if (!dstdir)
        return (1);
    buf = getcwd(NULL, 0);
    if (!buf)
        return (1);
    if (dstdir[0] == '/')
        newdir = ft_strdup(dstdir);
	else
		newdir = ft_strjoin_dir(buf, dstdir);
    if (!newdir)
        return (1);
	chdir(newdir);
	env_set(&msh->env, ft_strjoin("OLDPWD=", buf));
	env_set(&msh->env, ft_strjoin("PWD=", newdir));
	free(buf);
	free(newdir);
	return (0);
}
