/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_sort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/20 12:00:45 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 16:34:08 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "ft_glob.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_string.h"

static void	sortdir_recur(t_list **list, size_t depth);
static char	str_read(char const *str, size_t i);
static inline int	fill_buckets(t_list **list, t_list *b[128], size_t depth);

/**
 * @brief	Sort the contents of `pglob` in ascending ASCII order.
 */
void	glob_sortdir(t_list **dirl)
{
	sortdir_recur(dirl, 0);
}

static void	sortdir_recur(t_list **list, size_t depth)
{
	t_list	*buckets[128];
	int		c;

	if (!list)
		return ;
	ft_memset(buckets, 0x0, 128 * sizeof(t_list *));
	if (fill_buckets(list, buckets, depth) == 0)
		return (list_prepend(list, buckets[0]));
	list_prepend(list, buckets[0]);
	c = 1;
	while (c < 128)
	{
		if (buckets[c])
		{
			sortdir_recur(&buckets[c], depth + 1);
			list_prepend(list, buckets[c]);
		}
		c++;
	}
}

static char	str_read(char const *str, size_t i)
{
	if (i >= ft_strlen(str))
		return ('\0');
	return (str[i]);
}

static inline int	fill_buckets(t_list **list, t_list *b[128], size_t depth)
{
	size_t const	n = list_size(*list);
	int				c;

	if (n == 1)
		return (0);
	while (*list)
	{
		c = 0;
		while (c < 128 && *list)
		{
			if (str_read((*list)->content, depth) == c)
				list_push(&b[c], list_pop(list));
			c++;
		}
	}
	return (n != list_size(b[0]));
}
