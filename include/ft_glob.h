/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 14:33:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/19 15:43:40 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_H
# define FT_GLOB_H

#include "ft_list.h"
#include <limits.h>

enum e_glob_errno {
	GLOB_SUCCESS = 0,
	GLOB_MEMFAIL,
};

int	ft_glob(char const *pattern, t_list **glob);

#endif
