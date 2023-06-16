/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_append_val.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 18:23:39 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/14 18:24:09 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "msh_env.h"
#include "msh_error.h"
#include "msh_var.h"
#include <stdlib.h>

t_errno	env_append_val(t_env *env, char const *name)
{
	char const	*newentry;

	size_t const entry_i = env_entry_get(env, name);
	if (entry_i == env->len)
		return (MSH_NO_VARSTR);
	newentry = ft_strjoin(msh->env.envp[i], ft_strchr(name, '=') + 1);
	if (!newentry)
		return (MSH_MEMFAIL);
	free(msh->env.envp[i]);
	msh->env.envp[i] = newentry;
	return (MSH_SUCCESS);
}
