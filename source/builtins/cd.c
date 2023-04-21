/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:52:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/04/21 17:36:31 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <stdlib.h>
#include <unistd.h>

void	write_joined(char *string, size_t len1, size_t len2)
{
	int	i;

	i = 0;
	while (i < len1)
	{
		string[i] = *s1;
		++i;
		++s1;
	}
	string[i] = '/';
	++i;
	len2 += len1;
	while (i < len2)
	{
		string[i] = *s2;
		++i;
		++s2;
	}
}

char	*ft_strjoin_dir(char const *s1, char const *s2)
{
	char	*string;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	string = malloc((len1 + len2 + 2) * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		string[i] = *s1;
		++i;
		++s1;
	}
	string[i] = '/';
	++i;
	len2 += len1 + 1;
	while (i < len2)
	{
		string[i] = *s2;
		++i;
		++s2;
	}
	return (string);
}

int	main(int argc, char **argv)
{
	char	*buf;
	char	*newdir;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		return (1);
	newdir = ft_strjoin_dir(buf, argv[1]); // don't end path with a /
	free(buf);
	chdir(newdir);
	// update env
}
