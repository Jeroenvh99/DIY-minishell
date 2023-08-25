/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 14:43:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/25 13:27:48 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "list_utils.h"

#include "ft_glob.h"
#include "ft_list.h"
#include "ft_string.h"
#include <stdlib.h>

static inline t_errno	glob_noresult(t_list **words, char const *pattern);
static inline t_list	*glob_extract(t_ft_glob *pglob);

t_errno	expand_glob(t_list **words, char *pattern)
{
	t_ft_glob	pglob;

	ft_glob_init(&pglob);
	if (ft_glob(&pglob, pattern) != FT_GLOB_SUCCESS)
		return (ft_glob_destroy(&pglob), MSH_MEMFAIL);
	if (pglob.size == 0)
		return (glob_noresult(words, pattern));
	return (list_prepend(words, glob_extract(&pglob)), MSH_SUCCESS);
}

static inline t_errno	glob_noresult(t_list **words, char const *pattern)
{
	char *const	dup = ft_strdup(pattern);

	if (!dup)
		return (MSH_MEMFAIL);
	if (list_push_ptr(words, dup) != 0)
		return (free(dup), MSH_MEMFAIL);
	return (MSH_SUCCESS);
}

static inline t_list	*glob_extract(t_ft_glob *pglob)
{
	t_list	*list;

	list = NULL;
	while (pglob->globl)
		list_push(&list, list_pop(&pglob->globl));
	pglob->size = 0;
	return (list);
}
