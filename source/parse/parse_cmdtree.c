/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmdtree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:33:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/07 14:08:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

enum e_tags {
	TAG_PIPELINE = 0;
	TAG_OPERATOR;
};

enum e_stacks {
	OPS = 0;
	OUT;
};

struct s_tunion {
	int		tag;
	union	u_token {
		t_list	*pipeline;
		t_token	*operator
	}	data;
};

t_errno	parse_cmdtree(t_cmdtree **tree, t_list **tokens, t_msh *msh)
{
	t_list	*
	t_list	*pipeline;

	*base = cmdtree_init(parent);
	if (!*base)
		return (MSH_MEMFAIL);
	
}

static t_errno	ft_shunting_yard(t_list **input, t_msh *msh)
{
	t_list			*stack[2];
	struct s_tunion	*tunion;
	t_errno			errno;

	while (*input)
	{
		tunion = malloc(sizeof(struct s_tunion));
		if (tunion == NULL)
			return (MSH_MEMFAIL);
		if (!is_ctltok((t_token *)(*input)->content))
		{
			tunion->tag = TAG_PIPELINE; 
			errno = parse_pipeline(&tunion->data.pipeline, tokens, msh);
			if (errno != MSH_SUCCESS)
				return (list_clear(&ops, (t_freef)tunion_free));
			if (list_append_ptr(&stack[OUT]
		}
		
	}
	return (MSH_SUCCESS);
}

static void tunion_free(struct s_tunion *tunion)
{
	if (tunion->tag == TAG_PIPELINE)
		list_clear(tunion->data.pipeline, cmd_free);
	else
		free(tunion->data.token);
}
