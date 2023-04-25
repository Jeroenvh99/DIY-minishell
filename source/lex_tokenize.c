/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_tokenize.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:25:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:54:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_lex.h"
#include "msh_parse.h"

#include "ft_ctype.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static t_token	*token_get(char const **str);
static t_token	*token_get_word(char const **str);
static t_token	*token_get_qword(char const **str, t_toktype type);
static t_token	*token_get_meta(char const **str);

t_token	*lex_tokenize(char const **str)
{
	while (*str)
	{
		if (ft_isspace(**str))
			(*str)++;
		else
			return (token_get(str));
	}
	return (NULL);
}

static t_token	*token_get(char const **str)
{
	if (**str == CHR_DQUOTE)
		return (token_get_qword(str, TOK_WORD));
	if (**str == CHR_SQUOTE)
		return (token_get_qword(str, TOK_QWORD));
	if (is_metachr(**str))
		return (token_get_meta(str));
	return (token_get_word(str));
}

static t_token	*token_get_word(char const **str)
{
	t_token	*token;
	char	*word;
	size_t	len;

	len = 0;
	while ((*str)[len] && !is_metachr((*str)[len]))
		len++;
	word = ft_substr(*str, 0, len);
	if (word == NULL)
		return (NULL);
	token = token_init(word, TOK_WORD);
	if (token == NULL)
		return (free(word), NULL);
	*str += len;
	return (token);
}

static t_token	*token_get_qword(char const **str, t_toktype type)
{
	t_token		*token;
	char		*word;
	size_t		len;

	len = 1;
	while ((*str)[len++] != **str)
		;
	word = ft_substr(*str, 1, len - 2);
	if (word == NULL)
		return (NULL);
	token = token_init(word, type);
	if (token == NULL)
		return (free(word), NULL);
	*str += len;
	return (token);
}

static t_token	*token_get_meta(char const **str)
{
	char const *const	metatokens[N_TOK_META] = {
		TOK_PIPE_STR, TOK_STDIN_STR, TOK_STDOUT_STR,
		TOK_HEREDOC_STR, TOK_STDOUT_APPEND_STR,
		TOK_AND_STR, TOK_OR_STR};
	size_t const		metatokens_len[N_TOK_META] = {
		1, 1, 1, 2, 2, 2, 2,};
	t_toktype			type;

	type = N_TOK_META;
	while (type--)
	{
		if (!ft_strncmp(metatokens[type], *str, metatokens_len[type]))
			break ;
	}
	*str += metatokens_len[type];
	return (token_init(NULL, type + TOK_META_MIN));
}
