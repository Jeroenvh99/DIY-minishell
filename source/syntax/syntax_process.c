/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_process.c                                   :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:09:23 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/08 11:11:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"
#include "msh_token.h"
#include "msh_utils.h"

#include "ft_string.h"

static inline int	check_meta(int type, int *last, int params[N_PARAMS]);
static inline int	check_word(int type, int *last, int params[N_PARAMS]);

/**
* @brief	Detect a token and advance the string pointer to the next one.
* @return	
*/
int	syntax_process(char const **str, int *last, int params[N_PARAMS])
{
	int		type;
	size_t	len;

	type = token_read_meta(*str, &len);
	if (type == TOK_INVALID)
	{
		type = token_read_word(*str, &len, &params[QUOTE]);
		*str += len;
		return (check_word(type, last, params));
	}
	*str += len;
	return (check_meta(type, last, params));
}

/**
* @brief	Check whether the (meta)token of type `type` raises a syntax error.
* 			Also updates the value of `last` to the current type and adjusts
			the values in the params
* @return	A status code:
* 			SYNTAX_SUCCESS	Success or recoverable syntax error.
* 			SYNTAX_FATAL	Unrecoverable syntax error.
*/
static inline int	check_meta(int type, int *last, int params[N_PARAMS])
{
	if (token_is_redirection(*last))
		return (SYNTAX_FATAL);
	else if (type == TOK_PIPE || type == TOK_AND || type == TOK_OR)
	{
		params[OPERATOR] = type;
		if (*last == TOK_NONE || *last == TOK_PIPE || token_is_andor(*last))
			return (SYNTAX_FATAL);
	}
	else if (type == TOK_OPENPAR)
	{
		params[PARNS]++;
		if (*last == TOK_WORD || *last == TOK_PIPE)
			return (SYNTAX_FATAL);
	}
	else if (type == TOK_CLOSEPAR)
	{
		params[PARNS]--;
		if (params[PARNS] < 0 || *last != TOK_WORD)
			return (SYNTAX_FATAL);
	}
	*last = type;
	return (SYNTAX_SUCCESS);
}

static inline int	check_word(int type, int *last, int params[N_PARAMS])
{
	*last = type;
	if (type == TOK_WORD)
	{
		params[OPERATOR] = TOK_NONE;
		return (SYNTAX_SUCCESS);
	}
	return (SYNTAX_FATAL);
}
