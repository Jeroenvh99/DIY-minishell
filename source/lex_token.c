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

void	token_destroy(t_token **token)
{
	free((*token)->str);
	free(*token);
	*token = NULL;
}
