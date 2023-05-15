#include <stddef.h>

#include "ft_string.h"

char	*get_path(char *pathname)
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
}
