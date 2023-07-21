/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:31 by dbasting      #+#    #+#                 */
/*   Updated: 2023/07/21 17:10:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

#include "ft_string.h"
#include <limits.h>
#include <stddef.h>
#include <sys/stat.h>

static char const	*path_read(char *const buf, char const *path);
static int			ispathname(char const *name);

/* Test whether `filename` is also a pathname (i.e. contains a '/' character).
 * If `filename` is not a pathname, then `path` (the PATH variable should be 
 * supplied here) is split into segments which are prepended to `filename`; 
 * the resulting pathname is checked for validity.
 * The first valid pathname encountered is copied into `buf`.
 * @return	0: on success.
 * @return	1: if the resulting pathname exceeds PATH_MAX in length.
 */
int	get_pathname(char *const buf, char const *filename, char const *path)
{
	struct stat	sb;

	if (ispathname(filename))
	{
		buf[0] = '\0';
		return (ft_strlcat(buf, filename, PATH_MAX) > PATH_MAX);
	}
	if (path)
	{
		while (*path)
		{
			path = path_read(buf, path);
			if (ft_strlcat(buf, "/", PATH_MAX) > PATH_MAX)
				return (1);
			if (ft_strlcat(buf, filename, PATH_MAX) > PATH_MAX)
				return (1);
			if (stat(buf, &sb) == 0)
				return (0);
		}
	}
	return (1);
}

/* Copy a segment from `path` to `buf`.
 * @return	A pointer to the segment directly following the segment that was
 * 			copied.
 */
static char const	*path_read(char *const buf, char const *path)
{
	size_t	i;

	i = 0;
	while (path[i] && i < PATH_MAX)
	{
		if (path[i] == ':')
		{
			buf[i] = '\0';
			return (&path[i + 1]);
		}
		buf[i] = path[i];
		i++;
	}
	buf[i] = '\0';
	return (&path[i]);
}

/* Check whether `name` is a pathname. */
static int	ispathname(char const *name)
{
	while (*name)
	{
		if (*name == '/')
			return (1);
		name++;
	}
	return (0);
}
