/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:31 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/21 00:28:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include <stddef.h>
#include <sys/stat.h>
#include "ft_string.h"

int	get_pathname(char *buf, char const *filename, char const *path)
{
	struct stat sb; //mag NULL zijn?

	if (!ispathname(file) || !path)
	{
		while (*path)
		{
			path = path_read(buf, path);
			if (ft_strlcat(buf, filename, NAME_MAX) > NAME_MAX)
				return (1);
			if (stat(buf, &sb) == 0)
				return (0);
		}
		*buf = '\0';
	}
	return (ft_strlcat(buf, filename, NAME_MAX) > NAME_MAX);
}

char	*path_read(char *buf, char const *path)
{
	size_t	i;
	
	i = 0;
	while (path[i] && i < NAME_MAX)
	{
		if (buf[i] == ':')
		{
			i++;
			break ;
		}
		buf[i] = path[i];
		i++;
	}
	*buf = '\0';
	return (&path[i]);
}

int	ispathname(char const *name)
{
	while (*name)
	{
		if (*name == '/')
			return (1);
		name++;
	}
	return (0);
}

/*char	*get_path(char *pathname)
{
	size_t	len;

	len = ft_strlen(pathname);
	while (len--)
	{
		if (pathname[len] == '/')
			break ;
	}
	return (ft_substr(pathname, 0, len));
}

char	*get_filename(char *pathname)
{
	size_t	offset;

	offset = ft_strlen(pathname);
	while (offset && pathname[offset - 1] != '/')
		offset--;
	return (ft_strdup(pathname + offset));
}*/
