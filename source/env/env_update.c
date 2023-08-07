/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 10:37:04 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/01 23:02:55 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief	Check if `env` holds an entry under `name` and update it if it
 * does. Do nothing if the entry does not exist.
 * @return	An exit status:
 * 			- 0: `name` updated successfully.
 * 			- 1: `name` is not defined.
 * 			- 2: A memory allocation error occured.
 */
int	env_update(t_env *env, char const *name, char const *value)
{
	char *const	entry = env_entry_build(name, value);
	size_t		i;

	if (!entry)
		return (2);
	i = env_entry_get(env, name);
	if (!env->envp[i])
		return (free(entry), 1);
	free(env->envp[i]);
	env->envp[i] = entry;
	return (0);
}
