/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_readdir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 14:45:51 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 12:04:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "list_utils.h"

#include "ft_string.h"
#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>

static DIR	*glob_opendir(char const *path);

t_list	*glob_readdir(char const *path)
{
	t_list			*dirl;
	DIR *const		dir = glob_opendir(path);
	struct dirent	*dirent;
	t_entry			*entry;

	if (!dir)
		return (NULL);
	dirl = NULL;
	dirent = readdir(dir);
	while (dirent)
	{
		entry = malloc(sizeof(t_entry));
		if (!entry)
			return (closedir(dir), list_clear(&dirl, free), NULL);
		entry->d_name[0] = '\0';
		ft_strlcpy(entry->d_name, dirent->d_name, NAME_MAX);
		entry->d_type = dirent->d_type;
		if (list_push_ptr(&dirl, entry) != 0)
			return (closedir(dir), free(entry), list_clear(&dirl, free), NULL);
		dirent = readdir(dir);
	}
	return (closedir(dir), glob_sortdir(&dirl), dirl);
}

static DIR	*glob_opendir(char const *path)
{
	if (!path)
		return (NULL);
	if (path[0] == '\0')
		return (opendir("."));
	return (opendir(path));
}
