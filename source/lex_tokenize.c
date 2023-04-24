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

static char	*token_get(char const **str);
static char	*token_get_meta(char const **str);
static char	*token_get_qword(char const **str);
static char	*token_get_word(char const **str);

char	*lex_tokenize(char const **str)
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

static char	*token_get(char const **str)
{
	if (**str == CHR_SQUOTE || **str == CHR_DQUOTE)
		return (token_get_qword(str));
	if (is_metachr(**str))
		return (token_get_meta(str));
	return (token_get_word(str));
}

static char	*token_get_meta(char const **str)
{
	char const *const	metatokens[N_METATOK] = {
		TOK_PIPE, TOK_STDIN, TOK_STDOUT,
		TOK_HEREDOC, TOK_STDOUT_APPEND,
		TOK_AND, TOK_OR};
	size_t const		metatokens_len[N_METATOK] = {
		1, 1, 1, 2, 2, 2, 2,};
	size_t				i;

	i = N_METATOK;
	while (i--)
	{
		if (!ft_strncmp(metatokens[i], *str, metatokens_len[i]))
			break ;
	}
	*str += metatokens_len[i];
	return (ft_strdup(metatokens[i]));
}	

static char	*token_get_qword(char const **str)
{
	char	*token;
	size_t	len;

	len = 1;
	while ((*str)[len] != **str)
		len++;
	token = malloc((len + 1) * sizeof(char));
	if (token == NULL)
		return (NULL);
	(*str)++;
	ft_strlcat(token, *str, len + 1);
	*str += len;
	return (token);
}

static char	*token_get_word(char const **str)
{
	char	*token;
	size_t	len;

	len = 0;
	while ((*str)[len] && !is_metachr((*str)[len]))
		len++;
	token = malloc((len + 1) * sizeof(char));
	if (token == NULL)
		return (NULL);
	ft_strlcat(token, *str, len + 1);
	*str += len;
	return (token);
}
