/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:37:18 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/13 22:02:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_error.h"
#include "msh_utils.h"

#include "ft_string.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief	Initialize a buffer of size PATH_MAX, containing the current
			working directory.
 * @return	An exit status. Possible values:
 * 			MSH_SUCCESS	Success.
 * 			MSH_GENERIC Error (either memory allocation failed or getcwd()
 * 						failed for another reason).
 */
t_errno	cwd_init(t_buffer *cwd)
{
	cwd->b = getcwd(NULL, PATH_MAX);
	if (!cwd->b)
		return (MSH_GENERIC);
	cwd->size = PATH_MAX;
	return (MSH_SUCCESS);
}

/**
 * @brief	Update the current working directory, expanding the buffer in
			PATH_MAX-sized steps as required.
 * @return	An exit status. Possible values:
 * 			MSH_SUCCESS	Success.
 * 			MSH_GENERIC Error (either memory allocation failed or getcwd()
 * 						failed for another reason).
 */
t_errno	cwd_update(t_buffer *cwd)
{
	if (getcwd(cwd->b, cwd->size) != NULL)
		return (MSH_SUCCESS);
	free(cwd->b);
	cwd->b = getcwd(NULL, cwd->size + PATH_MAX);
	if (cwd->b == NULL)
	{
		cwd->size = 0;
		return (MSH_GENERIC);
	}
	cwd->size += PATH_MAX;
	return (MSH_SUCCESS);
}
