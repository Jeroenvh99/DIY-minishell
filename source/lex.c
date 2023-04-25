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
#include <stddef.h>
#include <stdlib.h>

static void	node_delete(void *node);

t_list	*lex(char const *str)
{
	t_list	*tokens;
	t_list	*node;
	t_token	*token;

	tokens = NULL;
	while (*str)
	{
		token = lex_tokenize(&str);
		if (token == NULL)
			return (list_delete(tokens, &node_delete), NULL);
		node = list_new(token);
		if (node == NULL)
			return (list_delete(tokens, &node_delete), NULL);
		list_append(&tokens, node);
	}
	return (tokens);
}

static void	node_delete(void *node)
{
	token_destroy(((t_list *)node)->content);
	free(node);
}
