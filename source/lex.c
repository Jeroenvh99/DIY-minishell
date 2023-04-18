/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 15:51:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

static void	node_delete(void *node);

t_list	*lex(char const *str)
{
	t_list	*tokens;
	t_list	*node;
	char	*token;

	tokens = NULL;
	while (*str)
	{
		token = lex_tokenize(&str);
		if (token == NULL)
			return (list_delete(tokens, &node_delete), NULL);
		node = list_new(token);
		if (token == NULL)
			return (list_delete(tokens, &node_delete), NULL);
		list_append(&tokens, node);
	}
	return (tokens);
}

static void	node_delete(void *node)
{
	free(((t_list *)node)->content);
	free(node);
}

int	main(int argc, char **argv)
{
	t_list	*tokens;

	if (argc != 2)
		return (1);
	tokens = lex((char const *)argv[1]);
	while (tokens)
	{
		printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
	return (0);
}
