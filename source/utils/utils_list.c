/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 18:14:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

t_list	*list_pop(t_list **lst)
{
	t_list	*node;

	if (!*lst)
		return (NULL);
	node = *lst;
	*lst = (*lst)->next;
	node->next = NULL;
	return (node);
}

void	*list_pop_ptr(t_list **lst)
{
	t_list	*node;
	void	*content;

	node = list_pop(lst);
	if (!node)
		return (NULL);
	content = node->content;
	free(node);
	return (content);
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

t_errno	list_push_ptr(t_list **lst, void *ptr)
{
	t_list	*node;

	node = list_new(ptr);
	if (node == NULL)
		return (MSH_MEMFAIL);
	list_push(lst, node);
	return (MSH_SUCCESS);
}
