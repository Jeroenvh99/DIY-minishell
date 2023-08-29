/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_treeacts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:40:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/15 15:24:27 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"

int	syntax_check_operator(int *last, int *pars)
{
	(void) pars;
	if (*last == NONE || *last == PIPE || *last == REDIRECT)
		return (SYNTERROR_FATAL);
	*last = OPERATOR;
	return (SUCCESS);
}

int	syntax_check_openpar(int *last, int *pars)
{
	(*pars)++;
	if (*last == WORD || *last == PIPE || *last == REDIRECT)
		return (SYNTERROR_FATAL);
	return (SUCCESS);
}

int	syntax_check_closepar(int *last, int *pars)
{
	(*pars)--;
	if (*pars < 0 || *last != WORD)
		return (SYNTERROR_FATAL);
	return (SUCCESS);
}
