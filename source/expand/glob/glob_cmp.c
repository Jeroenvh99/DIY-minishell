/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   glob_cmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 21:14:40 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 00:15:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"

#include <dirent.h>
#include "ft_string.h"

int	glob_cmp(char const *pattern, t_entry *entry)
{
	size_t	entry_len;

	if (entry->d_type == DT_DIR && pattern[ft_strlen(pattern) - 1] == '/')
	{
		entry_len = ft_strlen(entry->d_name);
		if (entry->d_name[entry_len - 1] != '/')
		{
			entry->d_name[entry_len++] = '/';
			entry->d_name[entry_len] = '\0';
		}
	}
	return (glob_patcmp(pattern, entry->d_name));
}
