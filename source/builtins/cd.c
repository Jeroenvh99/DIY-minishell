/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 17:56:51 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
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
	i = copy_str(s1, string, i, len1);
	string[i] = '/';
	++i;
	len2 += len1 + 1;
	i = copy_str(s2, string, i, len2);
	string[i] = '\0';
	return (string);
}

char	*get_env_dir(char *name, t_msh *msh)
{
	char	*dstdir;
	char	*errmsg;

	dstdir = get_env_var(name, msh->env);
	if (!dstdir)
	{
		errmsg = ft_strjoin(name, " not set");
		print_error("cd", NULL, errmsg);
		free(errmsg);
		return (0);
	}
	return (dstdir);
}

char	*get_dstdir(int argc, char **argv, t_msh *msh)
{
	char	*dstdir;

	dstdir = NULL;
	if (argc == 1 || ft_strncmp(argv[1], "--", 3) == 0)
	{
		dstdir = get_env_dir("HOME", msh);
	}
	else
	{
		if (ft_strncmp(argv[1], "-", 2) == 0)
		{
			dstdir = get_env_dir("OLDPWD", msh);
			ft_printf("%s\n", dstdir);
		}
		else
			dstdir = argv[1];
	}
	return (dstdir);
}

int	msh_cd(int argc, char **argv, t_msh *msh)
{
	char	*dstdir;
	char	*newdir;
	char	*buf;
	int		i;

	// check for invalid input
	dstdir = get_dstdir(argc, argv, msh);
	if (dstdir[0] == '/')
		newdir = ft_strdup(dstdir);
	else
	{
		buf = getcwd(NULL, 0);
		if (!buf)
			return (1);
		newdir = ft_strjoin_dir(buf, dstdir); 
	}
	chdir(newdir);
	i = remove_var("OLDPWD", msh->env);
	msh->env[i] = ft_strjoin("OLDPWD=", buf);
	i = remove_var("PWD", msh->env);
	msh->env[i] = ft_strjoin("PWD=", newdir);
	free(buf);
	free(newdir);
	return (0);
}

int	main(int argc, char **argv)
{
	msh_cd(argc, argv);
}