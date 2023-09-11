/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_append_val.c                                   :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 18:23:39 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/09/11 15:44:28 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "msh_env.h"
#include "msh_error.h"
#include "msh_var.h"
#include <stdlib.h>

t_errno	env_append_val(t_env *env, char *entry, char const *name)
{
	char			*newentry;
	size_t const	entry_i = env_entry_get(env, name);

	if (entry_i == env->len)
		return (MSH_INVVARID);
	newentry = ft_strjoin(env->envp[entry_i], ft_strchr(entry, '=') + 1);
	if (!newentry)
		return (MSH_MEMFAIL);
	free(env->envp[entry_i]);
	env->envp[entry_i] = newentry;
	return (MSH_SUCCESS);
}
