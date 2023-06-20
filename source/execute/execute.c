/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/06/20 22:11:41 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Execute `cmdtree`. `cmdtree` is consumed. */
t_errno	execute(t_list **pipeline, t_msh *msh)
{
	env_pack(&msh->env);
	return (execute_pipeline(pipeline, msh));
}

/* Execute all commands in `pipeline` `pipeline` is consumed. */
t_errno execute_pipeline(t_list **pipeline, t_msh *msh)
{
	t_cmd	*cmd;
	t_errno	errno;

	while (*pipeline)
	{
		cmd = list_pop_ptr(pipeline);
		errno = execute_cmd(cmd, msh);
		cmd_free(cmd);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
	}
	return (MSH_SUCCESS);
}
