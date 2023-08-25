/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmdtree.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:42:31 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 12:07:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

t_cmdtree	*cmdtree_init(t_cmdtree *parent)
{
	t_cmdtree *const	tree = ft_calloc(1, sizeof(t_cmdtree));

	if (!tree)
		return (NULL);
	tree->parent = parent;
	return (tree);
}

void	cmdtree_destroy(t_cmdtree **tree)
{
	if (!*tree)
		return ;
	if ((*tree)->op)
	{
		cmdtree_destroy(&(*tree)->data.branches[TREE_RIGHT]);
		cmdtree_destroy(&(*tree)->data.branches[TREE_LEFT]);
	}
	else
		list_clear(&(*tree)->data.pipeline, (t_freef)cmd_free);
	free(*tree);
	*tree = NULL;
}

void	cmdtree_free(t_cmdtree *tree)
{
	if (!tree)
		return ;
	if (!tree->op)
		list_clear(&tree->data.pipeline, (t_freef)cmd_free);
	free(tree);
}
