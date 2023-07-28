/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 10:37:04 by dbasting      #+#    #+#                 */
/*   Updated: 2023/07/28 10:47:35 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static char	*entry_build(char const *name, char const *value);

/* Check if `env` holds an entry under `name` and update it if it does. Do
 * nothing if the entry does not exist.
 */
int	env_update(t_env *env, char const *name, char const *value)
{
	char	*entry;
	size_t	i;

	i = env_entry_get(env, name);
	if (!env->envp[i])
		return (1);
	entry = entry_build(name, value);
	if (!entry)
		return (2);
	free(env->envp[i]);
	env->envp[i] = entry;
	return (0);
}

static char	*entry_build(char const *name, char const *value)
{
	char *const	entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	
	if (!entry)
		return (NULL);
	entry[0] = '\0';
	ft_strlcat(entry, name, -1);
	ft_strlcat(entry, "=", -1);
	ft_strlcat(entry, value, -1);
	return (entry);
}	

