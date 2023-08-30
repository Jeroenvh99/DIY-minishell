/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_operator.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 11:59:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"

t_errno	parse_and(t_cmdtree *tree, t_list **tokens, t_msh *msh)
{
	(void) tree;
	(void) msh;
	token_free(list_pop_ptr(tokens));
	return (MSH_SUCCESS);
}

t_errno	parse_or(t_cmdtree *tree, t_list **tokens, t_msh *msh)
{
	(void) tree;
	(void) msh;
	token_free(list_pop_ptr(tokens));
	return (MSH_SUCCESS);
}
