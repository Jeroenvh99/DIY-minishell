/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 12:30:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 15:46:53 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_var.h"
#include "msh.h"
#include "msh_error.h"

#include <stdlib.h>

/* Search local and environment variables for `name` and returns the value. Do
 * NOT attempt to modify this value. Return NULL if `name` is not set.
 */
char	*var_search(char const *name, t_msh *msh)
{
	return (env_search(&msh->env, name));
}
