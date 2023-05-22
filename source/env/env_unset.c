/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/22 16:17:45 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

#include <stddef.h>
#include <stdlib.h>

/* Remove `name` from `env`. Do nothing if `name` does not exist. */
void	env_unset(t_env	*env, char const *name)
{
	size_t const	entry_i = env_entry_get(env, name);

	if (entry_i == env->len)
		return ;
	free(env->envp[entry_i]);
	env->envp[entry_i] = NULL;
	env->used--;
}
