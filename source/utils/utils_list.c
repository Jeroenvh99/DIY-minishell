/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/25 13:28:48 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_utils.h"

#include "ft_list.h"
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

int	list_append_ptr(t_list **lst, void *ptr)
{
	t_list	*node;

	node = list_new(ptr);
	if (node == NULL)
		return (1);
	list_append(lst, node);
	return (0);
}

int	list_push_ptr(t_list **lst, void *ptr)
{
	t_list	*node;

	node = list_new(ptr);
	if (node == NULL)
		return (1);
	list_push(lst, node);
	return (0);
}

void	list_prepend(t_list **list, t_list *prefix)
{
	t_list *const	tail = list_last(prefix);

	if (!tail)
		return ;
	tail->next = *list;
	*list = prefix;
}
