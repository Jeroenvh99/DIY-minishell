/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob_utils.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 23:57:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 15:56:27 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_UTILS_H
# define FT_GLOB_UTILS_H

# include "ft_glob.h"

# include "ft_list.h"
# include <limits.h>

typedef struct s_entry {
	char	d_name[NAME_MAX + 2];
	int		d_type;
}	t_entry;

int		glob_cmp(char const *pat, t_entry *entry);
int		glob_patcmp(char const *pat, char const *name);

int		glob_add(t_ft_glob *pglob, char *path);
int		glob_add_join(t_ft_glob *pglob, char const *path, char const *name);

t_list	*glob_readdir(char const *path);
void	glob_sortdir(t_list **dirl);

#endif
