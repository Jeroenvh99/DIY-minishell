/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_actions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:31:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/14 16:44:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"

int	syntax_check_word(int *last, int *pars)
{
	(void) pars;
	*last = WORD;
	return (SUCCESS);
}

int	syntax_check_redir(int *last, int *pars)
{
	(void) pars;
	if (*last == REDIRECT)
		return (SYNTERROR_FATAL);
	*last = REDIRECT;
	return (SUCCESS);
}

int	syntax_check_pipe(int *last, int *pars)
{
	(void) pars;
	if (*last == PIPE || *last == REDIRECT || *last == NONE)
		return (SYNTERROR_FATAL);
	*last = PIPE;
	return (SUCCESS);
}
