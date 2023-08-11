/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:39:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/11 16:01:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"
#include "msh.h"

#include "ft_list.h"
#include "ft_string.h"

static int	check_final(int ct[N_CAT]);

/**
 * @brief	Perform a syntax check on a list of tokens.
 * @param	tokens	A linked list of tokens.
 * @return	An error code. Possible values:
 * 				0: No syntax errors were encountered.
 * 				1: At least one fatal syntax error was encountered.
 * 				2 or higher: A fixable syntax error (i.e. by supplying
 * 				additional tokens) was encountered.
 */
int	syntax_check(t_list *tokens)
{
	int				error;
	int				ct[N_CAT];
	t_action const	actions[N_TOK] = {
		syntax_check_word,
		syntax_check_redir, syntax_check_redir,
		syntax_check_redir, syntax_check_redir,
		syntax_check_pipe,
		syntax_check_operator, syntax_check_operator,
		syntax_check_openpar, syntax_check_closepar};

	ft_memset(ct, 0x0, N_CAT * sizeof(int));
	while (tokens)
	{
		error = actions[((t_token *)tokens->content)->type](ct);
		if (error != SUCCESS)
			return (error);
		tokens = tokens->next;
	}
	return (check_final(ct));
}

static int 	check_final(int ct[N_CAT])
{
	if (ct[PIPE] == 1)
		return (SYNTERROR_PIPE);
	if (ct[OPERATOR] == 1)
		return (SYNTERROR_OPERATOR);
	if (ct[PARENTHESIS] > 0)
		return (SYNTERROR_PARENTHESIS);
	if (ct[PARENTHESIS] < 0 || ct[REDIRECT] > 0)
		return (SYNTERROR_FATAL);
	return (SUCCESS);
}
