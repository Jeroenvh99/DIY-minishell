/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 17:16:52 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 17:40:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "ft_list.h"
# include <stddef.h>

typedef struct s_hashtable {
	size_t		base_size;
	t_list*		slots[];
}	t_hashtable;

size_t		hash(size_t max, char const *key);
t_hashtable	hashtable_init(size_t base_size);
int			hashtable_insert(char const *key, void *value);
void		*hashtable_lookup(char const *key);
void		*hashtable_remove(char const *key);
void		hashtable_destroy(t_hashtable **hashtable);

#endif
