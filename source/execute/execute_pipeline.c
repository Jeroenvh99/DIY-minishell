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
	t_fd		tube[2];

	if ((*pipeline)->next != NULL)
		return (execute_pipeline_subsh(pipeline, msh));
	while (*pipeline)
	{
		pipe(tube);
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
	t_fd	tube[2];
	t_fd	read;

	read = 0;
	while (*pipeline)
	{
		cmd = list_pop_ptr(pipeline);
		pipe(tube);
		msh->child = fork();
		if (msh->child == -1)
			return (msh_perror(0), MSH_FORKFAIL);
		if (msh->child == 0)
		{
			cmd->io[IO_IN] = read;
			cmd->io[IO_OUT] = tube[PIPE_WRITE];
			close(tube[PIPE_READ]);
			execute_subsh(cmd, msh);
		}
		if (read > 0)
		{
			close(read);
		}
		read = tube[PIPE_READ];
		close(tube[PIPE_WRITE]);
		cmd_free(cmd);
	}
	close(tube[PIPE_READ]);
	msh->exit = execute_wait(msh);
	return (MSH_SUCCESS);
}
