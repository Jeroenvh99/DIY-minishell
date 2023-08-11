/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmdtree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:33:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/04 16:06:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

struct s_tunion {
	int		tag;
	union	u_token {
		t_cmd	*cmd;
		t_token	*token
	}	data;
};

t_errno	parse_cmdtree(t_cmdtree **tree, t_list **tokens, t_msh *msh)
{
	t_list	*
	t_list	*pipeline;

	*base = cmdtree_init(parent);
	if (!*base)
		return (MSH_MEMFAIL);
	while (*tokens)
	{
		while (!is_ctltok
}

/*
 * '('					+L; cursor -> new
 * ')'					cursor -> parent
 * '||'					op = OR; +R; cursor -> new
 * '&&'					op = AND; +R; cursor -> new
 */
