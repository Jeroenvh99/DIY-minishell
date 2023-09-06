/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/29 10:16:20 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stddef.h>
#include <unistd.h>

static t_builtinf	get_builtin(char const *cmd);

/**
 * @brief	Main executor: either run a builtin function from `cmd` or pass its
 * 			members to execve(), forking as necessary. Set the "_" environment
 * 			variable to the value of the final element of `cmd`->argv.array.
 * @return	An exit status:
 * 			MSH_SUCCESS		Success.
 * 			MSH_FORKFAIL	Couldn't realize a fork.
 */
t_errno	execute_cmd(t_cmd *cmd, t_msh *msh)
{
	t_builtinf const	builtin = get_builtin(cmd->argv.array[0]);

	env_update(&msh->env, "_", cmd->argv.array[cmd->argc - 1]);
	if (builtin)
	{
		msh->exit = builtin(cmd, msh);
		return (MSH_SUCCESS);
	}
	return (execute_bin(cmd, msh));
}

/**
 * @brief	Check whether `cmd` matches the name of a builtin utility.
 * @return	A pointer to the utility function.
 * 			NULL if no utility was found.
 */
static t_builtinf	get_builtin(char const *cmd)
{
	t_builtinf const	builtins[N_BUILTIN] = {
		msh_cd, msh_echo, msh_env, msh_exit, msh_export, msh_pwd, msh_unset};
	char const *const	names[N_BUILTIN] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"};
	size_t				i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (i < N_BUILTIN)
	{
		if (ft_strncmp(cmd, names[i], -1) == 0)
			return (builtins[i]);
		i++;
	}
	return (NULL);
}
