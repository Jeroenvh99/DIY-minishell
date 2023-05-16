/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 17:31:20 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"
#include "msh_var.h"

#include "ft_string.h"
#include <stddef.h>

/* Return the index of the entry `envp` defining `name`. If `name` is not
 * defined in `envp`, the index will point to the terminating NULL pointer.
 */
size_t	env_entry_get(char **envp, char const *name)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (env_entry_getval(envp[i], name))
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
