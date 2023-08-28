/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*       dbasting <dbasting@student.codam.nl>        +#+                      */
/*   Created: 2023/05/16 15:12:17 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/25 13:27:27 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief	Execute and consume the current command tree. */
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
