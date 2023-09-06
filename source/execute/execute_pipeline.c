/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipeline.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 16:06:56 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/28 15:21:20 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include <stddef.h>
#include <unistd.h>

static t_errno	execute_pipeline_subsh(t_list **pipeline, t_msh *msh);

/**
 * @brief	Execute all commands in `pipeline`. If `pipeline` contains more
 * 			than one simple command, spawn a subshell for every command.
 * 			`pipeline` is consumed.
 * @return	An exit status.
 */
t_errno	execute_pipeline(t_list **pipeline, t_msh *msh)
{
	t_cmd		*cmd;
	t_errno		errno;

	if ((*pipeline)->next != NULL)
		return (execute_pipeline_subsh(pipeline, msh));
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

static t_errno	execute_pipeline_subsh(t_list **pipeline, t_msh *msh)
{
	t_cmd	*cmd;

	while (*pipeline)
	{
		cmd = list_pop_ptr(pipeline);
		msh->child = fork();
		if (msh->child == -1)
			return (msh_perror(0), MSH_FORKFAIL);
		if (msh->child == 0)
			execute_subsh(cmd, msh);
		msh->exit = execute_wait(msh);
		cmd_free(cmd);
		msh->child = 0;
	}
	return (MSH_SUCCESS);
}
