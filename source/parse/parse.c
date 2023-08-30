/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 11:58:33 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"
#include <stdlib.h>

/* Parse `tokens` to form a command tree. `tokens` is consumed. */
t_errno	parse(t_msh *msh, t_list **tokens)
{
	return (parse_cmdtree(&msh->tree, tokens, msh));
}

/* Throw an MSH_SYNTAX_ERROR if an invalid token is encountered. This should
 * never happen. If it does, the lexer is likely broken.
 */
t_errno	parse_invalid(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	(void) cmd;
	(void) tokens;
	(void) msh;
	return (MSH_SYNTAX_ERROR);
}
