/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 19:55:25 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 16:06:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_H
# define FT_GLOB_H

# include "ft_list.h"

enum e_glob_errno {
	FT_GLOB_SUCCESS = 0,
	FT_GLOB_NOTFOUND,
	FT_GLOB_FAIL,
	FT_GLOB_MEMFAIL,
};

typedef struct s_ft_glob	t_ft_glob;

struct s_ft_glob {
	t_list		*globl;
	size_t		size;
};

int		ft_glob(t_ft_glob *pglob, char const *pattern);
void	ft_glob_init(t_ft_glob *pglob);
void	ft_glob_destroy(t_ft_glob *pglob);

#endif
