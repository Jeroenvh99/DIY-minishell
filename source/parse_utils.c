/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 11:50:28 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:05:48 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"

#include "ft_list.h"
#include <stdlib.h>

t_cmd	*cmd_get_current(t_list *cmds)
{
	t_list	*cmd_node;

	cmd_node = list_last(cmds);
	if (!cmd_node)
		return (NULL);
	return ((t_cmd *)cmd_node->content);
}

t_token	*token_pop(t_list **tokens)
{
	t_list	*node;
	t_token	*token;

	node = *tokens;
	if (!node)
		return (NULL);
	*tokens = node->next;
	token = node->content;
	free(node);
	return (token);
}