/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/28 15:55:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stddef.h>

static t_builtinf	get_builtin(char const *cmd);

/* Execute `cmd` */
t_errno	execute_cmd(t_cmd *cmd, t_msh *msh)
{
	t_builtinf const	builtin = get_builtin(cmd->argv.array[0]);

	if (builtin)
		return (execute_builtin(builtin, cmd, msh));
	return (execute_bin(cmd, msh));
}

/* Check whether the `cmd` string matches the name of a builtin utility.
 * @return: A pointer to the utility function if found, or NULL otherwise. 
 */
static t_builtinf	get_builtin(char const *cmd)
{
	t_builtinf const	builtins[N_BUILTIN] = {
		msh_cd, msh_echo, msh_env, msh_exit, msh_pwd, msh_unset};
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
