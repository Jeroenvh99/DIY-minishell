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

static t_errno		expand_loop(t_expstr *expstr, t_msh *msh);
static inline t_expop		get_expop(char c, t_quote *lquote, size_t *exp_len);
static inline int			expand_process_quote(char c, t_quote *lquote);

//Expands the string stored in `str` to a list of words. This consumes `*str`!
t_errno	expand(t_list **words, char **str, t_msh *msh)
{
	t_expstr	expstr;
	t_errno		errno;

	expstr.str = *str;
	expstr.ops = malloc((ft_strlen(expstr.str) + 1) * sizeof(t_expop));
	if (expstr.ops == NULL)
		return (MSH_MEMFAIL);
	expstr.i = 0;
	errno = expand_loop(&expstr, msh);
	if (errno != MSH_SUCCESS)
		return (free(expstr.str), free(expstr.ops), errno);
	errno = expand_fieldsplit(words, &expstr);
	free(expstr.str);
	free(expstr.ops);
	*str = NULL;
	return (errno);
}

static t_errno	expand_loop(t_expstr *expstr, t_msh *msh)
{
	t_quote	lquote;
	size_t	exp_len;
	t_errno	errno;

	lquote = NOQUOTE;
	exp_len = 0;
	while (expstr->str[expstr->i])
	{
		if (!exp_len && lquote != SQUOTE && expstr->str[expstr->i] == CHR_VAR)
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

static inline t_expop	get_expop(char c, t_quote *lquote, size_t *exp_len)
{
	if (*exp_len)
	{
		if (*lquote == NOQUOTE && ft_isspace(c))
			return (EXPOP_ENDW);
		(*exp_len)--;
	}
	else if (expand_process_quote(c, lquote))
		return (EXPOP_SKIP);
	return (EXPOP_COPY);
}

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
