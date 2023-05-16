/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 17:31:20 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

#include <stddef.h>
#include <stdlib.h>

void	env_unset(t_env	*env, char const *name)
{
	size_t	entry_i;

	entry_i = env_entry_get(env->envp, name);
	if (env->envp[entry_i] == NULL)
		return ;
	free(env->envp[entry_i]);
	while (entry_i < env->used)
	{
		env->envp[entry_i] = env->envp[entry_i + 1];
		entry_i++;
	}
	env->envp[entry_i] = NULL;
	env->used--;
}
