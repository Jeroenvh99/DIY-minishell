/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:41:15 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/08 11:10:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"
#include "msh_utils.h"

#include "ft_string.h"
#include <stddef.h>

static inline int	read_quote(char c, int *quote);

/**
* @brief	Read a command line token from a string and store its length.
* @param	str	The string to read from.
* @param	len	A pointer to the length of this token.
* @return	The type of the token that was read.
*/
int	token_read(char const *str, size_t *len)
{
	int	type;
	int	quote;

	type = token_read_meta(str, len);
	quote = NOQUOTE;
	if (type == TOK_INVALID)
	{
		type = token_read_word(str, len, &quote);
		if (quote != NOQUOTE)
			return (-quote);
	}
	return (type);
}

/**
* @brief	Detect a non-word token.
* @return	The type of the token that was detected (ranging from TOK_STDIN
* 			to TOK_CLOSEPAR), or TOK_INVALID in case no special token was found.
*/
int	token_read_meta(char const *str, size_t *len)
{
	char const *const	toks[N_TOK_META] = {
		TOK_STDIN_STR, TOK_HEREDOC_STR,
		TOK_STDOUT_STR, TOK_STDOUT_APPEND_STR,
		TOK_PIPE_STR,
		TOK_AND_STR, TOK_OR_STR,
		TOK_OPENPAR_STR, TOK_CLOSEPAR_STR};
	size_t const		toks_len[N_TOK_META] = {1, 2, 1, 2, 1, 2, 2, 1, 1};
	int					type;

	type = N_TOK_META;
	while (type--)
	{
		if (ft_strncmp(toks[type], str, toks_len[type]) == 0)
		{
			*len = toks_len[type];
			return (type + TOK_META_MIN);
		}
	}
	*len = 0;
	return (TOK_INVALID);
}

/**
* @brief	Detect a word token.
* @param	str		The string to read.
* @param	len		The length of the word will be stored here.
* @param	quote	If the word contains unclosed quotes, either SQUOTE or
* 					DQUOTE will be stored here.
* @return	The type of the token that was read (TOK_WORD).
*/
int	token_read_word(char const *str, size_t *len, int *quote)
{
	*len = 0;
	while (str[*len])
	{
		read_quote(str[*len], quote);
		if (*quote == NOQUOTE && ft_strchr(METACHARS, str[*len]) != NULL)
			break ;
		(*len)++;
	}
	if (*len == 0)
		return (TOK_NONE);
	return (TOK_WORD);
}

/**
* @brief	Process a quote character.
* @param	c		The character that was read.
* @param	quote	The result of the last successful call to this function.
* 					E.g. if the previous call processed an opening single quote,
* 					this parameter will hold SQUOTE.
* @return	An exit status:
* 			0	Reading this character did not result in a change to the current
* 				quote state. This will be returned on reading anything other
* 				than a single or double quote, or when reading a quote that was
* 				either escaped or itself enclosed in another type of quotation.
* 			1	The current quote state was changed. This will be returned upon
* 				reading an opening or closing quote character.
*/
static inline int	read_quote(char c, int *quote)
{
	if (*quote == NOQUOTE)
	{
		if (c == '\'')
		{
			*quote = SQUOTE;
			return (1);
		}
		else if (c == '\"')
		{
			*quote = DQUOTE;
			return (1);
		}
	}
	else if ((*quote == SQUOTE && c == '\'')
		|| (*quote == DQUOTE && c == '\"'))
	{
		*quote = NOQUOTE;
		return (1);
	}
	return (0);
}
