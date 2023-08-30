/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_fieldsplit.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 16:11:49 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

static inline int	exp_strlen(t_expop *ops, size_t *wlen, size_t *opsn);
static inline int	exp_strncpy(char *word, t_expstr *expstr, size_t opsn);

t_errno	expand_fieldsplit(t_list **words, t_expstr *expstr)
{
	char	*word;
	size_t	wlen;
	size_t	opsn;
	int		glob;

	expstr->i = 0;
	while (expstr->str[expstr->i])
	{
		while (expstr->ops[expstr->i] == EXPOP_ENDW)
			expstr->i++;
		glob = exp_strlen(&expstr->ops[expstr->i], &wlen, &opsn);
		word = malloc((wlen + 1) * sizeof(char));
		if (word == NULL)
			return (MSH_MEMFAIL);
		exp_strncpy(word, expstr, opsn);
		if (glob)
		{
			if (expand_glob(words, word) == MSH_MEMFAIL)
				return (free(word), MSH_MEMFAIL);
			free(word);
		}
		else if (list_push_ptr(words, word) != 0)
			return (free(word), MSH_MEMFAIL);
	}
	return (MSH_SUCCESS);
}

/**
 * @brief	Determine the length of the next field, storing it in `wlen`.
 * @return	A status code:
 * 			0: Success.
 * 			1: At least one EXPOP_GLOB operation was encountered: the resulting
 * 			string can be treated as a ft_glob pattern.
 */
static inline int	exp_strlen(t_expop *ops, size_t *wlen, size_t *opsn)
{
	int		ret;

	*wlen = 0;
	*opsn = 0;
	ret = 0;
	while (ops[*opsn] && ops[*opsn] != EXPOP_ENDW)
	{
		if (ops[*opsn] == EXPOP_COPY)
			(*wlen)++;
		else if (ops[*opsn] == EXPOP_GLOB)
		{
			ret = 1;
			(*wlen)++;
		}
		(*opsn)++;
	}
	return (ret);
}

static inline int	exp_strncpy(char *word, t_expstr *expstr, size_t opsn)
{
	while (opsn--)
	{
		if (expstr->ops[expstr->i] == EXPOP_COPY
			|| expstr->ops[expstr->i] == EXPOP_GLOB)
			*(word++) = expstr->str[expstr->i];
		expstr->i++;
	}
	*word = '\0';
	return (0);
}
