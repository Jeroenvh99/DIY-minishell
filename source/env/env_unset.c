/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/11 15:45:04 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"
#include <stddef.h>
#include <stdlib.h>

/* Remove `name` from `env`. Do nothing if `name` does not exist. */
t_errno	env_unset(t_env	*env, char const *name)
{
	size_t const	entry_i = env_entry_get(env, name);

	if (entry_i == env->len)
		return (MSH_INVVARID);
	free(env->envp[entry_i]);
	env->envp[entry_i] = NULL;
	env->used--;
	return (MSH_SUCCESS);
}
