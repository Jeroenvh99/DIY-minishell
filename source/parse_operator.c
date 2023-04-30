/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_meta.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_stdlib.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

t_errno	parse_and(t_list **token_list, t_cmdtable *cmdtable)
{
	t_list	*node;

	(void) cmdtable;
	node = *token_list;
	*token_list = (*token_list)->next;
	list_delete(node, free);
	return (MSH_SUCCESS);
}

t_errno	parse_or(t_list **token_list, t_cmdtable *cmdtable)
{
	t_list	*node;

	(void) cmdtable;
	node = *token_list;
	*token_list = (*token_list)->next;
	list_delete(node, free);
	return (MSH_SUCCESS);
}
