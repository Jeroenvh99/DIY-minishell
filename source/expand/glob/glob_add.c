/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob_add.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 20:27:02 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/22 09:45:57 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "ft_glob.h"
#include "ft_string.h"
#include "list_utils.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief	Add a result to `pglob`.
 */
int	glob_add(t_ft_glob *pglob, char *path)
{
	t_list *const	node = list_new(path);

	if (!node)
		return (FT_GLOB_MEMFAIL);
	list_prepend(&pglob->globl, node);
	pglob->size++;
	return (FT_GLOB_SUCCESS);
}

/**
 * @brief	Create a filesystem entry from `path` and `name` and add it to
 * 			`pglob`.
 */
int	glob_add_join(t_ft_glob *pglob, char const *path, char const *name)
{
	char	*subpath;

	subpath = ft_strjoin(path, name);
	if (!subpath || glob_add(pglob, subpath) != FT_GLOB_SUCCESS)
		return (free(subpath), FT_GLOB_MEMFAIL);
	return (FT_GLOB_SUCCESS);
}
