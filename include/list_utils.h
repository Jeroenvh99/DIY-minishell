/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 11:45:32 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 16:34:44 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_UTILS_H
# define LIST_UTILS_H

# include "ft_list.h"

typedef void	(*t_freef)(void *);

/* List functions. */
int		list_append_ptr(t_list **lst, void *ptr);
t_list	*list_pop(t_list **lst);
void	*list_pop_ptr(t_list **lst);
int		list_push_ptr(t_list **lst, void *ptr);
void	list_prepend(t_list **list, t_list *prefix);

#endif
