/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/18 14:45:51 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/24 11:13:16 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

static DIR	*glob_opendir(char const *path);

t_list	*glob_readdir(char const *path)
{
	t_list			*dirl;
	DIR *const		dir = glob_opendir(path);
	struct dirent	*dirent;

	if (!dir)
		return (NULL);
	dirl = NULL;
	dirent = readdir(dir);
	return (closedir(dir), dirl);
}

static DIR	*glob_opendir(char const *path)
{
	if (!path)
		return (NULL);
	if (path[0] == '\0')
		return (opendir("."));
	return (opendir(path));
}
