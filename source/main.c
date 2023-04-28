/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_parse.h"

#include "ft_list.h"
#include <stdio.h>

static void	token_free_wrapper(void *token);

int	main(void)
{
	t_list	*tokens;
	t_list	*ptr;

	tokens = NULL;
	input_get(&tokens, PROMPT);
	ptr = tokens;
	while (ptr)
	{
		printf("(%d) %s\n", ((t_token *)ptr->content)->type, ((t_token *)ptr->content)->str);
		ptr = ptr->next;
	}
	list_clear(&tokens, token_free_wrapper);
	return (0);
}

static void	token_free_wrapper(void *token)
{
	token_free(token);
}
