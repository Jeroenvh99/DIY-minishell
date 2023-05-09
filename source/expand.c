/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 12:23:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 18:19:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_ctype.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

static t_errno		expand_loop(t_expstr *expstr, t_quote *lquote,
						size_t *exp_len, t_msh *msh);
static inline int	expand_process_quote(char c, t_quote *lquote);

t_errno	expand(t_list **words, t_msh *msh)
{
	t_expstr	expstr;
	t_quote		lquote;
	size_t		exp_len;
	t_errno		errno;

	expstr.str = (*words)->content;
	expstr.ops = malloc((ft_strlen(expstr.str) + 1) * sizeof(t_expop));
	if (expstr.ops == NULL)
		return (MSH_MEMFAIL);
	list_clear(words, NULL);
	lquote = NOQUOTE;
	exp_len = 0;
	expstr.i = 0;
	errno = expand_loop(&expstr, &lquote, &exp_len, msh);
	if (errno != MSH_SUCCESS)
		return (free(expstr.str), free(expstr.ops), errno);
	errno = expand_fieldsplit(&expstr, words);
	free(expstr.str);
	free(expstr.ops);
	return (errno);	
}

//Iterate over expstr.str and fill expstr->ops according to quotes and escapes.

//move lquote and exp_len inside function
static t_errno	expand_loop(t_expstr *expstr, t_quote *lquote, size_t *exp_len,
								t_msh *msh)
{
	t_expop	op;
	t_errno	errno;

	errno = MSH_SUCCESS;
	while (expstr->str[expstr->i])
	{
		op = EXPOP_COPY;
		if (*exp_len)
		{
			(*exp_len)--;
			if (*lquote == NOQUOTE && ft_isspace(expstr->str[expstr->i]))
				op = EXPOP_ENDW;
		}
		else
		{
			if (expand_process_quote(expstr->str[expstr->i], lquote))
				op = EXPOP_SKIP;
			else if (*lquote != SQUOTE && expstr->str[expstr->i] == CHR_VAR)
				errno = expand_dollar(expstr, exp_len, msh);
		}
		if (errno != MSH_SUCCESS)
			return (errno);
		expstr->ops[expstr->i++] = op;
	}
	expstr->ops[expstr->i] = EXPOP_ENDP;
	return (MSH_SUCCESS);
}

//t_expop	determine_expop()

static inline int	expand_process_quote(char c, t_quote *lquote)
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
