/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 17:28:50 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 17:40:15 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

#include "ft_list.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

t_hashtable	*hashtable_init(size_t base_size)
{
	t_hashtable	table;

	table = malloc(sizeof(t_hashtable));
	if (table == NULL)
		return (NULL);
	table->base_size = 0;
	table->slots = malloc(sizeof(t_list *));
	if (table_slots == NULL)
		return (free(table), NULL);
	while (table->base_size < base_size)
	{
		table->slots[table->base_size] = ft_calloc(sizeof(t_list));
		if (table->slots[table->base_size] == NULL)
			return (hashtable_destroy(&table), NULL);
		table->base_size++;
	}
	return (table);
}

void	hashtable_destroy(t_hashtable **hashtable, void (*del)(void *))
{
	while ((*hashtable)->base_size--)
		list_clear((*hashtable)->slots[(*hashtable)->base_size], del);
	free((*hashtable)->slots);
	free(*hashtable);
	*hashtable = NULL;
}
