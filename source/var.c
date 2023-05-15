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

t_errno	var_search(char **value, char const *name, t_msh *msh)
{
	return (get_env_var(name, value, msh->env));
}
