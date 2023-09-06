/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 00:13:40 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 15:55:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "ft_glob_utils.h"
#include "list_utils.h"

#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>

static t_list	*glob_patsplit(char const *pattern);
static int		glob_recur(t_ft_glob *pglob, char *cwd, t_list *patl);
static void		cleanup(t_entry *d, t_list **dirl);

int	ft_glob(t_ft_glob *pglob, char const *pattern)
{
	t_list		*patl;
	char *const	root = malloc(NAME_MAX + 2);
	int			ret;

	if (pattern[0] == '\0')
		return (free(root), FT_GLOB_SUCCESS);
	if (!root)
		return (perror("ft_glob"), FT_GLOB_MEMFAIL);
	patl = glob_patsplit(pattern);
	if (!patl)
		return (perror("ft_glob"), free(root), FT_GLOB_FAIL);
	root[0] = '\0';
	ret = glob_recur(pglob, root, patl);
	free(root);
	list_clear(&patl, free);
	if (ret != FT_GLOB_SUCCESS)
		ft_glob_destroy(pglob);
	return (ret);
}

static t_list	*glob_patsplit(char const *pattern)
{
	t_list	*list;
	char	*segment;
	size_t	i;

	list = NULL;
	while (*pattern)
	{
		i = 0;
		while (pattern[i])
		{
			if (pattern[i++] == '/')
			{
				while (pattern[i] == '/')
					i++;
				break ;
			}
		}
		segment = ft_substr(pattern, 0, i);
		if (!segment || list_append_ptr(&list, segment) != 0)
			return (free(segment), list_clear(&list, free), NULL);
		pattern += i;
	}
	return (list);
}

static int	glob_recur(t_ft_glob *pglob, char *cwd, t_list *patl)
{
	t_list	*dirl;
	t_entry	*d;
	char	*subpath;

	dirl = glob_readdir(cwd);
	while (dirl)
	{
		d = list_pop_ptr(&dirl);
		if (glob_cmp(patl->content, d))
		{
			subpath = ft_strjoin(cwd, d->d_name);
			if (!subpath)
				return (cleanup(d, &dirl), FT_GLOB_FAIL);
			if (patl->next)
			{
				if (glob_recur(pglob, subpath, patl->next) != FT_GLOB_SUCCESS)
					return (free(subpath), cleanup(d, &dirl), FT_GLOB_FAIL);
				free(subpath);
			}
			else
				glob_add(pglob, subpath);
		}
		free(d);
	}
	return (cleanup(NULL, &dirl), FT_GLOB_SUCCESS);
}

static void	cleanup(t_entry *d, t_list **dirl)
{
	free(d);
	list_clear(dirl, free);
}
