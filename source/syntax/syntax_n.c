/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 15:01:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 16:09:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_syntax.h"
#include "msh_parse.h"

#include "ft_ctype.h"
#include "ft_string.h"

static int	syntax_process(char const **str, int params[N_PARAMS]);
static int	syntax_process_quote(char c, int *quotes);
/**
 * @brief	Perform a syntax check on a string.
 * @param	str		The string to check.
 * @param	params	An array of integers representing:
 * 				[QUOTE]	The type of quote to close.
 * 				[CTL]	The control token to complete.
 * 				[PARNS]	The number of parentheses to close.
 *					If the command is spread out across several strings,
 * 					these values could be different from zero; e.g. if the
 * 					preceding substring contained an unclosed double quote,
 * 					params[QUOTE] should be equal to DQUOTE.
 * @return	A status code:
 * 			SYNTAX_SUCCESS	No unrecoverable errors were encountered.
 * 			SYNTAX_FATAL	An unrecoverable syntax error (e.g. incomplete
 * 							redirection, extraneous closing parenthesis) was
 * 							encountered.
 */
int	syntax(char const *str, int params[N_PARAMS])
{
	int	last;

	last = NONE;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (syntax_process(**str, &last, params) == SYNTAX_FATAL)
			return (SYNTAX_FATAL);
	}
	return ();
}
