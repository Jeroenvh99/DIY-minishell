/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdtree.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:42:31 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 14:32:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdlib.h"
#include <stdlib.h>

t_cmdtree	*cmdtree_init(t_cmdtree *parent)
{
	t_cmdtree *const	tree = ft_calloc(1, sizeof(t_cmdtree));

	if (!tree)
		return (NULL);
	tree->parent = parent;
	return (tree);
}

void	cmdtree_free(t_cmdtree *tree)
{
	if (!tree)
		return ;
	if (tree->op)
		return (cmdtree_free(tree->data.branches[TREE_RIGHT]),
			cmdtree_free(tree->data.branches[TREE_LEFT]));
	list_clear(&tree->data.pipeline, (t_freef)cmd_free);
	free(tree);
}
