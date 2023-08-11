/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_actions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:31:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/11 16:04:14 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"

int	syntax_check_word(int ct[N_CAT])
{
	ct[WORDS]++;
	ct[REDIRECT] = 0;
	ct[PIPE] = 0;
	ct[OPERATOR] = 0;
	return (SUCCESS);
}

int	syntax_check_redir(int ct[N_CAT])
{
	if (ct[REDIRECT] != 0)
		return (SYNTERROR_FATAL);
	ct[REDIRECT] = 1;
	return (SUCCESS);
}

int	syntax_check_pipe(int ct[N_CAT])
{
	if (ct[PIPE] != 0)
		return (SYNTERROR_FATAL);
	ct[PIPE] = 1;
	return (SUCCESS);
}
