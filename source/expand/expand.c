/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 12:23:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 12:53:52 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_ctype.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno		exp_loop(t_expstr *expstr, t_msh *msh);
static inline t_expop		get_expop(char c, t_quote *lquote, size_t *exp_len);
static inline int			exp_process_quote(char c, t_quote *lquote);

/**
 * @brief	Expand the string stored in `str`. If the parameter `words` is
 * 			supplied, word splitting will be performed on the expanded `str`
 * 			and the individual words will be appended to `words`.
 */
t_errno	expand(t_list **words, char **str, t_msh *msh)
{
	t_expstr	expstr;
	t_errno		errno;

	expstr.str = ft_strdup(*str);
	if (expstr.str == NULL)
		return (MSH_MEMFAIL);
	expstr.ops = malloc((ft_strlen(expstr.str) + 1) * sizeof(t_expop));
	if (expstr.ops == NULL)
		return (free(expstr.str), MSH_MEMFAIL);
	expstr.i = 0;
	errno = exp_loop(&expstr, msh);
	if (errno != MSH_SUCCESS)
		return (free(expstr.str), free(expstr.ops), errno);
	if (words)
		errno = expand_fieldsplit(words, &expstr);
	free(*str);
	*str = expstr.str;
	free(expstr.ops);
	return (errno);
}

/**
 * @brief	Loop through `expstr`->str, inserting expansions into it
 * as necessary and writing expansion operations to `expstr`->ops.
 * @return	A status code:
 * 			MSH_SUCCESS	on success
 * 			MSH_MEMFAIL	on memory allocation error.
 */
static t_errno	exp_loop(t_expstr *expstr, t_msh *msh)
{
	t_quote	lquote;
	size_t	exp_len;
	t_errno	errno;

	lquote = NOQUOTE;
	exp_len = 0;
	while (expstr->str[expstr->i])
	{
		if (!exp_len && lquote != SQUOTE && expstr->str[expstr->i] == '$')
		{
			errno = expand_dollar(expstr, &exp_len, msh);
			if (errno != MSH_SUCCESS)
				return (errno);
			continue ;
		}
		expstr->ops[expstr->i] = get_expop(expstr->str[expstr->i],
				&lquote, &exp_len);
		expstr->i++;
	}
	expstr->ops[expstr->i] = EXPOP_ENDP;
	return (MSH_SUCCESS);
}

/* @brief	Return the expansion operation, based on the current quote mode and
 * 			whether the current part of the string was inserted during an
 * 			expansion.
 * @return	An expansion operation:
 * 			EXPOP_COPY	Include this character in the final result.
 * 			EXPOP_SKIP	Exclude this character from the final result.
 * 			EXPOP_ENDW	Signifies a word boundary.
 */
static inline t_expop	get_expop(char c, t_quote *lquote, size_t *exp_len)
{
	if (*exp_len)
	{
		if (*lquote == NOQUOTE && ft_isspace(c))
			return (EXPOP_ENDW);
		(*exp_len)--;
	}
	else if (exp_process_quote(c, lquote))
		return (EXPOP_SKIP);
	if (*lquote == NOQUOTE && (c == '*' || c == '?'))
		return (EXPOP_GLOB);
	return (EXPOP_COPY);
}

/**
 * @brief	Alter the value of `lquote` to denote the current quote mode.
 * @return	1 if the quote mode was changed, 0 if it was unchanged. 
 */
static inline int	exp_process_quote(char c, t_quote *lquote)
{
	t_quote const	rquote = is_quote(c);

	if (*lquote == NOQUOTE)
	{
		if (rquote != NOQUOTE)
		{
			*lquote = rquote;
			return (1);
		}
	}
	else if (rquote == *lquote)
	{
		*lquote = NOQUOTE;
		return (1);
	}
	return (0);
}
