/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/01 23:43:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"

#include "ft_string.h"

t_errno	env_set(t_env *env, char const *name, char const *value)
{
	char *const	entry = env_entry_build(name, value);

	if (!entry)
		return (MSH_MEMFAIL);
	return (env_set_main(env, entry));
}

t_errno	env_set_entry(t_env *env, char const *entry)
{
	char *const	copy = ft_strdup(entry);

	if (copy == NULL)
		return (MSH_MEMFAIL);
	return (env_set_main(env, copy));
}
