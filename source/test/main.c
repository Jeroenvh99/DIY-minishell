/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

#include "ft_list.h"
#include <stdio.h>

int	main(void)
{
	t_list	*tokens;

	tokens = lex("Magnificat \"anima mea\" Dominum, et exsultavit 'spiritus meus' in>Deo salutari meo, "
				"quia respexit << humilitatem>>ancillae|suae; \"ecce | enim\" ex>hoc beatam<me&&dicent omnes||generationes");
	while (tokens)
	{
		printf("(%d) %s\n", ((t_token *)tokens->content)->type, ((t_token *)tokens->content)->str);
		tokens = tokens->next;
	}
	return (0);
}
