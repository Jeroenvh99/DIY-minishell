/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 15:52:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"
#include "msh_parse.h"
#include "msh_utils.h"
#include "list_utils.h"

#include "ft_ctype.h"
#include "ft_list.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno	catch_incomplete_token(t_list *tail_node, char const **str);
static t_errno	process(t_list **tokens, char const **str);
static t_errno	process_incomplete(t_token *token, char const **str);
static int		token_extract(t_list **tokens, int t, size_t l, char const **s);

t_errno	lex(t_list **tokens, char const *str)
{
	t_list *const	tail_node = list_last(*tokens);
	t_errno			errno;

	if (!str)
		return (MSH_SUCCESS);
	errno = catch_incomplete_token(tail_node, &str);
	if (errno != MSH_SUCCESS)
		return (errno);
	return (process(tokens, &str));
}

static t_errno	catch_incomplete_token(t_list *tail_node, char const **str)
{
	if (!tail_node || !tail_node->content)
		return (MSH_SUCCESS);
	if (((t_token *)tail_node->content)->type < 0)
		return (process_incomplete(tail_node->content, str));
	return (MSH_SUCCESS);
}

static t_errno	process(t_list **tokens, char const **str)
{
	int		type;
	size_t	len;

	type = TOK_NONE;
	while (**str)
	{
		if (ft_isspace(**str))
		{
			(*str)++;
			continue ;
		}
		type = token_read(*str, &len);
		if (type == TOK_INVALID)
			return (MSH_GENERIC);
		if (token_extract(tokens, type, len, str) != 0)
			return (MSH_MEMFAIL);
	}
	if (token_is_unclosed(type))
		return (MSH_INCOMPLETE_TOKEN);
	return (MSH_SUCCESS);
}

static t_errno	process_incomplete(t_token *token, char const **str)
{
	int		quote;
	size_t	len;
	char	*nstr;

	quote = -(token->type);
	token->type = token_read_word(*str, &len, &quote);
	nstr = ft_strnjoin(token->str, *str, len);
	if (!nstr)
		return (MSH_MEMFAIL);
	free(token->str);
	token->str = nstr;
	*str += len;
	return (MSH_SUCCESS);
}

static int	token_extract(t_list **tokens, int t, size_t len, char const **str)
{
	t_token *const	token = malloc(sizeof(t_token));

	if (!token)
		return (1);
	token->type = t;
	if (t == TOK_WORD || t == TOK_TRUNC || t == TOK_TRUNC_DQUOTE)
	{
		token->str = ft_substr(*str, 0, len);
		if (!token->str)
			return (free(token), 1);
	}
	else
		token->str = NULL;
	*str += len;
	if (list_append_ptr(tokens, token) != 0)
		return (token_free(token), 1);
	return (0);
}
