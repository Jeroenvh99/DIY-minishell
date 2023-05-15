/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strjoin_dir_test.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 12:15:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 12:33:18 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include <stdio.h>
#include <stdlib.h>

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

int	main()
{
	char *dir;

	dir = NULL;
	dir = ft_strjoin_dir("/Users/jvan-hal", "unset_test/"); // test for a dir with a slash at the end
	printf("%s\n", dir);
	free(dir);
	dir = NULL;
	dir = ft_strjoin_dir("/Users/jvan-hal", "unset_test"); // test for a dir without slash
	printf("%s\n", dir);
	free(dir);
	dir = NULL;
	dir = ft_strjoin_dir("/Users/jvan-hal", "unset"); // test for a file
	printf("%s\n", dir);
	free(dir);
	return (0);
}