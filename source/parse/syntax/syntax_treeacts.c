/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_treeacts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:40:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/14 16:52:38 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"

int	syntax_check_operator(int *last, int *pars)
{
	(void) pars;
	if (*last == NONE || *last == REDIRECT || *last == PIPE)
		return (SYNTERROR_FATAL);
	*last = OPERATOR;
	return (SUCCESS);
}

int	syntax_check_openpar(int *last, int *pars)
{
	(*pars)++;
	if (*last == REDIRECT || *last == PIPE)
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
