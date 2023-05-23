/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/22 16:45:42 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"
#include "msh_var.h"

#include "ft_string.h"
#include <stdlib.h>

#define REALLOC_SIZE	3

static t_errno	env_append(t_env *env, char *entry);
static t_errno	env_insert(t_env *env, char *entry);
static t_errno	env_realloc(t_env *env, char *entry);
static t_errno	env_overwrite(char **old_entry, char *entry);

/* Sets (a copy of) entry as an environment variable.
 */
t_errno	env_set(t_env *env, char const *entry)
{
	char *const	copy = ft_strdup(entry);
	char		*name;
	size_t		entry_i;
	t_errno		errno;

	if (copy == NULL)
		return (MSH_MEMFAIL);
	errno = var_parse(&name, NULL, entry);
	if (errno != MSH_SUCCESS)
		return (free(copy), errno);
	entry_i = env_entry_get(env, name);
	free(name);
	if (env->envp[entry_i])
		return (env_overwrite(&env->envp[entry_i], copy));
	else
		errno = env_append(env, copy);
	if (errno != MSH_SUCCESS)
		return (free(copy), errno);
	return (MSH_SUCCESS);
}

/* Append (i.e. do not overwrite) `entry`.
 */
static t_errno	env_append(t_env *env, char *entry)
{
	if (env->used < env->len)
		return (env_insert(env, entry));
	return (env_realloc(env, entry));
}

/* Insert `entry` into `env` without reallocating.
 */
static t_errno	env_insert(t_env *env, char *entry)
{
	size_t	i;

	i = 0;
	while (env->envp[i])
		i++;
	env->envp[i] = entry;
	env->used++;
	return (MSH_SUCCESS);
}

/* Reallocate `env` to hold REALLOC_SIZE more entries and insert `entry`.
 */
static t_errno	env_realloc(t_env *env, char *entry)
{
	char	**nenvp;

	nenvp = (char **)malloc((env->used + REALLOC_SIZE + 1) * sizeof(char *));
	if (nenvp == NULL)
		return (MSH_MEMFAIL);
	ft_memcpy(nenvp, env->envp, env->len * sizeof(char *));
	nenvp[env->len] = entry;
	env->used++;
	env->len += REALLOC_SIZE;
	ft_memset(&nenvp[env->used], 0, REALLOC_SIZE * sizeof(char *));
	free(env->envp);
	env->envp = nenvp;
	return (MSH_SUCCESS);
}

/* Overwrite `old_entry` with `entry`.
 */
static t_errno	env_overwrite(char **old_entry, char *entry)
{
	free(*old_entry);
	*old_entry = entry;
	return (MSH_SUCCESS);
}