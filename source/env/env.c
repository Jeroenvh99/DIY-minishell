/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/01 23:40:46 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <stddef.h>
#include <stdlib.h>

static size_t	env_len(char **envp);

/* Initialize the environment `env` (creating a copy of `envp`).
 */
t_errno	env_init(t_env *env, char **envp)
{
	env->len = env_len(envp);
	env->envp = (char **)malloc(sizeof(char *) * (env->len + 1));
	if (env->envp == NULL)
		return (MSH_MEMFAIL);
	env->used = 0;
	while (envp[env->used])
	{
		env->envp[env->used] = ft_strdup(envp[env->used]);
		if (env->envp[env->used] == NULL)
			return (env_free(env), MSH_MEMFAIL);
		env->used++;
	}
	env->envp[env->used] = NULL;
	if (env_basevars_set(env) != MSH_SUCCESS)
		return (env_free(env), MSH_MEMFAIL);
	return (MSH_SUCCESS);
}

/* Free the environment `env`.
 */
void	env_free(t_env *env)
{
	while (env->used--)
		free(env->envp[env->used]);
	free(env->envp);
}

static size_t	env_len(char **envp)
{
	size_t	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}
