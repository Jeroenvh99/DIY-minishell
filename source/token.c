/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

#include <stdlib.h>

t_token	*token_init(char *str, t_toktype type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = str;
	token->type = type;
	return (token);
}

void	token_free(t_token *token)
{
	free(token->str);
	free(token);
}

void	token_destroy(t_token **token)
{
	token_free(*token);
	*token = NULL;
}
