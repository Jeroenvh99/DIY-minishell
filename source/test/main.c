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

#include "lex.h"

#include "ft_list.h"
#include <stdio.h>

int	main(void)
{
	t_list	*tokens;

	tokens = lex("lorem ipsum $dolor 'sit amet' \"consectetur adipiscing\" elit");
	while (tokens)
	{
		printf("%s\n", (char *)tokens->content);
		tokens = tokens->next;
	}
	return (0);
}
