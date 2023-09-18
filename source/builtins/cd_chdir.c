/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_chdir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 22:03:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/13 22:37:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_error.h"

#include "ft_string.h"
#include <limits.h>
#include <unistd.h>

/**
 * @brief	Update the value of the shell-internal cwd variable (NOT to be
 * 			confused with the OLDPWD and PWD environment variables) and attempt
 * 			to update the current working directory.
 * @return	A status code. Possible values:
 * 			0	Success.
 * 			1	The target directory did not exist.
 * @note	
 */
int	cd_chdir(char *cwd, char const *path)
{
	ft_strlcpy(msh->cwd, path, PATH_MAX - 1);

}
