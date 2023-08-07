/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/07 17:02:18 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "msh_debug.h"
#include <stdlib.h>

/* Parse `tokens` to form a command tree. `tokens` is consumed. */
t_errno	parse(t_msh *msh, t_list **tokens)
{
	t_list	**pipeline;
	t_errno	errno;

	pipeline = &msh->cmds;
	ft_shuntingyard(pipeline, tokens, msh);
	shuntingyard_view(*pipeline);
	exit(0);
	while (*tokens)
	{
		if (is_ctltok((*tokens)->content))
			token_free(list_pop_ptr(tokens));
		errno = parse_pipeline(pipeline, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (errno);
	}
	return (MSH_SUCCESS);
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
