/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 12:12:55 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_parse.h"
#include "list_utils.h"

#include "ft_ctype.h"
#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno	catch_incomplete_token(t_list *tail_node, char const **str);
static t_errno	get_tokens(t_list **token_list, char const **str);

t_errno	lex(t_list **token_list, char const *str)
{
	t_list *const	tail_node = list_last(*token_list);
	t_errno			errno;

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
		if (is_metachr(**str))
			token = token_get_meta(str);
		else
			token = token_get_word(str);
		if (token == NULL)
			return (MSH_MEMFAIL);
		if (list_append_ptr(token_list, token) != 0)
			return (token_destroy(&token), MSH_MEMFAIL);
	}
	if (token && token->type < 0)
		return (MSH_INCOMPLETE_TOKEN);
	return (MSH_SUCCESS);
}
