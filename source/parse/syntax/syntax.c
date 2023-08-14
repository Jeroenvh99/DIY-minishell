/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 12:39:01 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/14 17:04:58 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"
#include "msh.h"

#include "ft_list.h"

static inline int	check_final(int last, int pars);

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
	int				last;
	int				pars;
	t_action const	actions[N_TOK] = {
		syntax_check_word,
		syntax_check_redir, syntax_check_redir,
		syntax_check_redir, syntax_check_redir,
		syntax_check_pipe,
		syntax_check_operator, syntax_check_operator,
		syntax_check_openpar, syntax_check_closepar};

	last = NONE;
	pars = 0;
	while (tokens)
	{
		error = actions[((t_token *)tokens->content)->type](&last, &pars);
		if (error != SUCCESS)
			return (error);
		tokens = tokens->next;
	}
	return (check_final(last, pars));
}

static inline int	check_final(int last, int pars)
{
	if (last == PIPE)
		return (SYNTERROR_PIPE);
	if (last == OPERATOR)
		return (SYNTERROR_OPERATOR);
	if (pars > 0)
		return (SYNTERROR_PARENTHESIS);
	if (pars < 0 || last == REDIRECT)
		return (SYNTERROR_FATAL);
	return (SUCCESS);
}
