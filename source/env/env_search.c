/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_search.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/22 14:34:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

#include <stddef.h>

/* Search `env` for the variable `name`. Return a pointer to the value portion
 * of the entry in question, or NULL if `name` was not found.
 */
char	*env_search(t_env *env, char const *name)
{
	size_t	i;
	char	*value;

	i = 0;
	while (i < env->len)
	{
		value = env_entry_getval(env->envp[i], name);
		if (value)
			return (value);
		i++;
	}
	return (NULL);
}
