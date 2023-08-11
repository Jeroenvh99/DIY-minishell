/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_treeacts.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:40:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/11 15:41:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"

int	syntax_check_operator(int ct[N_CAT])
{
	if (ct[OPERATOR] != 0
		|| (ct[WORDS] == 0 && ct[PIPE] == 0))
		return (SYNTERROR_FATAL);
	ct[OPERATOR] = 1;
	return (SUCCESS);
}

int	syntax_check_openpar(int ct[N_CAT])
{
	ct[PARENTHESIS]++;
	if (ct[WORDS] > 0)
		return (SYNTERROR_FATAL);
	ct[OPERATOR] = 0;
	return (SUCCESS);
}

int	syntax_check_closepar(int ct[N_CAT])
{
	ct[PARENTHESIS]--;
	if (ct[PARENTHESIS] < 0)
		return (SYNTERROR_FATAL);
	ct[OPERATOR] = 0;
	return (SUCCESS);
}
