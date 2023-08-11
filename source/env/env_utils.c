/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/07 10:43:27 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"
#include "msh_var.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <stddef.h>
#include <stdlib.h>

/* Construct an environment string from `name` and `value`. */
char	*env_entry_build(char const *name, char const *value)
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

/* Return the index of the entry in `env` defining `name`. If `name` is not
 * defined in `envp`, the index will be equal to env->len.
 */
size_t	env_entry_get(t_env *env, char const *name)
{
	size_t	i;

	i = 0;
	while (i < env->len)
	{
		if (env_entry_getval(env->envp[i], name))
			return (i);
		i++;
	}
	return (i);
}

/* Return a pointer to the value segment of `entry`. Return NULL if `entry`
 * does not define `name`.
 */
char	*env_entry_getval(char const *entry, char const *name)
{
	if (!entry || !name)
		return (NULL);
	while (*entry != '=')
	{
		if (*entry != *name)
			return (NULL);
		entry++;
		name++;
	}
	if (*name == '\0')
		return ((char *)entry + 1);
	return (NULL);
}

/* Pack the contents of `env` together - remove intervening NULL pointers. */
void	env_pack(t_env *env)
{
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	while (i + offset < env->len)
	{
		while (i + offset < env->len && !env->envp[i + offset])
			offset++;
		env->envp[i] = env->envp[i + offset];
		i++;
	}
	env->envp[i] = NULL;
}
