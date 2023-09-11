/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 12:50:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 12:50:31 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_utils.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t const	len = ft_strlen(s1) + n;
	char *const		str = malloc(sizeof(char) * (len + 1));

	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
