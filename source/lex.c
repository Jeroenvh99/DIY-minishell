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

#include "msh.h"
#include "msh_parse.h"
#include "msh_utils.h"

#include "ft_ctype.h"
#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno	catch_incomplete_token(t_list *tail_node, char const **str);
static t_errno	get_tokens(t_list **token_list, char const **str);
static t_token	*get_token(char const **str);

t_errno	lex(t_list **token_list, char const *str)
{
	t_list		*tail_node;
	t_errno		errno;

	tail_node = list_last(*token_list);
	errno = catch_incomplete_token(tail_node, &str);
	if (errno != MSH_SUCCESS)
		return (errno);
	return (get_tokens(token_list, &str));
}

static t_errno	catch_incomplete_token(t_list *tail_node, char const **str)
{
	if (!tail_node || !tail_node->content)
		return (MSH_SUCCESS);
	if (((t_token *)tail_node->content)->type < 0)
		return (token_complete(tail_node->content, str));
	return (MSH_SUCCESS);
}

static t_errno	get_tokens(t_list **token_list, char const **str)
{
	t_token	*token;

	token = NULL;
	while (**str)
	{
		if (ft_isspace(**str))
		{
			(*str)++;
			continue ;
		}
		token = get_token(str);
		if (token == NULL)
			return (MSH_MEMFAIL);
		if (list_append_ptr(token_list, token) != MSH_SUCCESS)
			return (token_destroy(&token), MSH_MEMFAIL);
	}
	if (token && token->type < 0)
		return (MSH_INCOMPLETE_TOKEN);
	return (MSH_SUCCESS);
}

static t_token	*get_token(char const **str)
{
	if (**str == CHR_DQUOTE)
		return (token_get_qword(str, TOK_WORD));
	if (**str == CHR_SQUOTE)
		return (token_get_qword(str, TOK_QWORD));
	if (is_metachr(**str))
		return (token_get_meta(str));
	return (token_get_word(str));
}
