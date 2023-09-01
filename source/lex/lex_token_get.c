/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_token_get.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:25:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 16:29:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_utils.h"

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static inline size_t	token_strlen(char const **str, t_quote *quote);
static inline t_errno	token_strjoin(t_token *token, char const *str,
							size_t len);

t_errno	token_complete(t_token *token, char const **str)
{
	t_quote	quote;
	size_t	len;

	quote = -(token->type);
	len = token_strlen(str, &quote);
	token->type = -(quote);
	if (token_strjoin(token, *str, len) != MSH_SUCCESS)
		return (MSH_MEMFAIL);
	*str += len;
	if (token->type < 0)
		return (MSH_INCOMPLETE_TOKEN);
	return (MSH_SUCCESS);
}

t_token	*token_get_word(char const **str)
{
	t_token	*token;
	t_quote	quote;
	size_t	len;

	token = token_init(NULL, TOK_WORD);
	if (token == NULL)
		return (NULL);
	quote = NOQUOTE;
	len = token_strlen(str, &quote);
	if (token_strjoin(token, *str, len) != MSH_SUCCESS)
		return (token_destroy(&token), NULL);
	token->type = -(quote);
	*str += len;
	return (token);
}

t_token	*token_get_meta(char const **str)
{
	*str += metatokens_len[type];
	return (token_init(NULL, type + TOK_META_MIN));
}

static inline size_t	token_strlen(char const **str, t_quote *quote)
{
	size_t	len;

	len = 0;
	while ((*str)[len])
	{
		if (*quote == NOQUOTE)
		{
			if (is_metachr((*str)[len]))
				break ;
			*quote = is_quote((*str)[len]);
		}
		else if (is_quote((*str)[len]) == *quote)
			*quote = NOQUOTE;
		len++;
	}
	return (len);
}

static inline t_errno	token_strjoin(t_token *token, char const *str,
							size_t len)
{
	char	*appendix;
	char	*new_word;

	appendix = ft_substr(str, 0, len);
	if (appendix == NULL)
		return (MSH_MEMFAIL);
	if (token->str == NULL)
	{
		token->str = appendix;
		return (MSH_SUCCESS);
	}
	new_word = ft_strjoin(token->str, appendix);
	free(appendix);
	if (new_word == NULL)
		return (MSH_MEMFAIL);
	free(token->str);
	token->str = new_word;
	return (MSH_SUCCESS);
}
