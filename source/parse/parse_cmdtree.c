/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmdtree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:33:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 11:58:50 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include <stdlib.h>

static t_errno		ft_shuntingyard(t_list **out, t_list **input, t_msh *msh);
static t_errno		shyard_read(t_cmdtree **node, t_list **input, t_msh *msh);
static t_errno		shyard_push(t_cmdtree *node, t_list **ctl, t_list **out);
static t_cmdtree	*rpl_convert(t_list **rpl);

t_errno	parse_cmdtree(t_cmdtree **tree, t_list **tokens, t_msh *msh)
{
	t_list	*rpl;
	t_errno	errno;

	rpl = NULL;
	errno = ft_shuntingyard(&rpl, tokens, msh);
	if (errno != MSH_SUCCESS)
		return (list_clear(&rpl, (t_freef)cmdtree_free), errno);
	*tree = rpl_convert(&rpl);
	return (errno);
}

t_errno	ft_shuntingyard(t_list **out, t_list **input, t_msh *msh)
{
	t_list		*ctl;
	t_cmdtree	*node;
	t_errno		errno;

	ctl = NULL;
	while (*input)
	{
		errno = shyard_read(&node, input, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(&ctl, (t_freef)cmdtree_free), errno);
		if (node->op)
		{
			errno = shyard_push(node, out, &ctl);
			if (errno != MSH_SUCCESS)
				return (list_clear(&ctl, (t_freef)cmdtree_free), errno);
		}
		else if (list_append_ptr(out, node) != 0)
			return (list_clear(&ctl, (t_freef)cmdtree_free), MSH_MEMFAIL);
	}
	while (ctl)
		if (((t_cmdtree *)(ctl->content))->op <= TREE_OP_OPENPAR)
			list_append(out, list_pop(&ctl));
	return (MSH_SUCCESS);
}

static t_errno	shyard_read(t_cmdtree **node, t_list **input, t_msh *msh)
{
	t_errno	errno;

	*node = cmdtree_init(NULL);
	if (!*node)
		return (MSH_MEMFAIL);
	if (!is_ctltok((*input)->content))
	{
		(*node)->op = TREE_OP_NONE;
		errno = parse_pipeline(&(*node)->data.pipeline, input, msh);
		if (errno != MSH_SUCCESS)
			return (cmdtree_free(*node), errno);
	}
	else
	{
		(*node)->op = ((t_token *)(*input)->content)->type - TOK_CTL_MIN + 1;
		free(list_pop_ptr(input));
	}
	return (MSH_SUCCESS);
}

static t_errno	shyard_push(t_cmdtree *node, t_list **out, t_list **ctl)
{
	if (node->op == TREE_OP_OPENPAR)
		return (list_push_ptr(ctl, node));
	if (node->op == TREE_OP_CLOSEPAR)
	{
		while (*ctl && ((t_cmdtree *)(*ctl)->content)->op != TREE_OP_OPENPAR)
			list_append(out, list_pop(ctl));
		if (!*ctl)
			return (MSH_SYNTAX_ERROR);
		cmdtree_free(list_pop_ptr(ctl));
		return (cmdtree_free(node), MSH_SUCCESS);
	}
	else
		while (*ctl && ((t_cmdtree *)(*ctl)->content)->op != TREE_OP_OPENPAR)
			list_append(out, list_pop(ctl));
	return (list_push_ptr(ctl, node));
}

static t_cmdtree	*rpl_convert(t_list **rpl)
{
	t_list		*tmp;
	t_list		*node;
	t_cmdtree	*leaf;

	tmp = NULL;
	while (*rpl)
	{
		node = list_pop(rpl);
		leaf = node->content;
		if (leaf->op)
		{
			leaf->data.branches[TREE_RIGHT] = list_pop_ptr(&tmp);
			leaf->data.branches[TREE_RIGHT]->parent = leaf;
			leaf->data.branches[TREE_LEFT] = list_pop_ptr(&tmp);
			leaf->data.branches[TREE_LEFT]->parent = leaf;
		}
		list_push(&tmp, node);
	}
	return (list_pop_ptr(&tmp));
}
