/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 17:42:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/19 17:53:49 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_exec.h"

#include "ft_string.h"
#include <stddef.h>

t_builtinf	is_builtin(char const *cmd)
{
	t_builtinf const	builtins[N_BUILTIN] = {
		cd, echo, env, exit, pwd, unset};
	char const *const	names[N_BUILTIN] = {
		"cd", "echo", "env", "exit", "pwd", "unset"};
	size_t				i;

	i = 0;
	while (i < N_BUILTIN)
	{
		if (ft_strncmp(cmd, names[i], -1) == 0)
			return (builtins[i]);
		i++;
	}
	return (NULL);
}
