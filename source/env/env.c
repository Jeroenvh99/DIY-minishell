/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 17:31:20 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"

#include "ft_string.h"
#include "ft_stdio.h"
#include <stddef.h>
#include <stdlib.h>

static size_t	env_len(char **envp);

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
	return (MSH_SUCCESS);
}

void	env_free(t_env *env)
{
	while (env->used--)
		free(env->envp[env->used]);
	free(env->envp);
	env->envp = NULL;
	env->len = 0;
}

static size_t	env_len(char **envp)
{
	size_t	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}
