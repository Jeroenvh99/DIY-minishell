/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/15 14:34:15 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* Execute `cmdtree`. `cmdtree` is consumed. */
t_errno	execute(t_msh *msh)
{
	t_errno	errno;
	
	handler_set(SIGINT, handle_relay);
	handler_set(SIGQUIT, handle_relay);
	env_pack(&msh->env);
	errno = execute_cmdtree(msh->tree, msh);
	return (cmdtree_destroy(&msh->tree), errno);
}

/* Execute a command tree `tree`. */
t_errno	execute_cmdtree(t_cmdtree *tree, t_msh *msh)
{
	t_errno	errno;

	if (!tree)
		return (MSH_SUCCESS);
	if (!tree->op)
		return (execute_pipeline(&tree->data.pipeline, msh));
	errno = execute_cmdtree(tree->data.branches[TREE_LEFT], msh);
	if (errno != MSH_SUCCESS)
		return (errno);
	if ((msh->g_msh->exit == EXIT_SUCCESS && tree->op == TREE_OP_AND)
		|| (msh->g_msh->exit != EXIT_SUCCESS && tree->op == TREE_OP_OR))
		return (execute_cmdtree(tree->data.branches[TREE_RIGHT], msh));
	return (MSH_SUCCESS);
}

/* Execute all commands in `pipeline` `pipeline` is consumed. */
t_errno	execute_pipeline(t_list **pipeline, t_msh *msh)
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
