/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_token_get.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:25:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:54:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_lex.h"
#include "msh_parse.h"

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno	token_str_append(t_token *token, char const *appendix);

t_errno	token_complete(t_token *token, char const **str)
{
	char	quote;
	char	*appendix;
	size_t	len;

	if (token->type == -TOK_QWORD)
		quote = CHR_SQUOTE;
	else
		quote = CHR_DQUOTE;
	len = 0;
	while ((*str)[len] && (*str)[len] != quote)
		len++;
	if ((*str)[len] == '\0')
	{
		if (token_str_append(token, *str) != MSH_SUCCESS)
			return (MSH_MEMFAIL);
		*str += len;
		return (MSH_INCOMPLETE_TOKEN);
	}
	token->type *= -1;
	appendix = ft_substr(*str, 0, len);
	if (token_str_append(token, appendix) != MSH_SUCCESS)
		return (free(appendix), MSH_MEMFAIL);
	*str += len + 1;
	free(appendix);
	return (MSH_SUCCESS);
}
//\n moet worden ingevoegd!

static t_errno	token_str_append(t_token *token, char const *appendix)
{
	char	*str_new;

	if (appendix == NULL)
		return (MSH_MEMFAIL);
	str_new = ft_strjoin(token->str, appendix);
	if (str_new == NULL)
		return (MSH_MEMFAIL);
	free(token->str);
	token->str = str_new;
	return (MSH_SUCCESS);
}

t_token	*token_get_word(char const **str)
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

t_token	*token_get_qword(char const **str, t_toktype type)
{
	t_token		*token;
	char		*word;
	size_t		len;

	len = 1;
	while ((*str)[len] != **str && (*str)[len])
		len++;
	if ((*str)[len] == '\0')
		type *= -1;
	word = ft_substr(*str, 1, len - 1);
	if (word == NULL)
		return (NULL);
	token = token_init(word, type);
	if (token == NULL)
		return (free(word), NULL);
	*str += len + (type > 0);
	return (token);
}

t_token	*token_get_meta(char const **str)
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
