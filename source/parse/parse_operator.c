/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_meta.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 15:17:26 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_list.h"
#include <stdlib.h>

t_errno	parse_and(t_list **tokens, t_list **cmds)
{
	(void) cmds;
	free(token_pop(tokens));
	return (MSH_SUCCESS);
}

t_errno	parse_or(t_list **tokens, t_list **cmds)
{
	(void) cmds;
	free(token_pop(tokens));
	return (MSH_SUCCESS);
}
