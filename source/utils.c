/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#include <stdlib.h>

void	free_ptr_array(void **array, size_t size)
{
	while (size--)
		free(array[size]);
	free(array);
}

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

t_errno	list_append_ptr(t_list **lst, void *ptr)
{
	t_list	*node;

	node = list_new(ptr);
	if (node == NULL)
		return (MSH_MEMFAIL);
	list_append(lst, node);
	return (MSH_SUCCESS);
}
