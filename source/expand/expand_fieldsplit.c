/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_fieldsplit.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:06 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 12:11:00 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh_error.h"
#include "list_utils.h"

#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

static inline void	exp_strlen(t_expop *ops, size_t *wlen, size_t *opsn);
static inline void	exp_strncpy(char *word, t_expstr *expstr, size_t opsn);

t_errno	expand_fieldsplit(t_list **words, t_expstr *expstr)
{
	char	*word;
	size_t	wlen;
	size_t	opsn;

	expstr->i = 0;
	while (expstr->str[expstr->i])
	{
		while (expstr->ops[expstr->i] == EXPOP_ENDW)
			expstr->i++;
		exp_strlen(&expstr->ops[expstr->i], &wlen, &opsn);
		word = malloc((wlen + 1) * sizeof(char));
		if (word == NULL)
			return (MSH_MEMFAIL);
		exp_strncpy(word, expstr, opsn);
		if (list_push_ptr(words, word) != 0)
			return (free(word), MSH_MEMFAIL);
	}
	return (MSH_SUCCESS);
}

static inline void	exp_strlen(t_expop *ops, size_t *wlen, size_t *opsn)
{
	*wlen = 0;
	*opsn = 0;
	while (ops[*opsn] && ops[*opsn] != EXPOP_ENDW)
	{
		if (ops[*opsn] == EXPOP_COPY)
			(*wlen)++;
		(*opsn)++;
	}
}

static inline void	exp_strncpy(char *word, t_expstr *expstr, size_t opsn)
{
	while (opsn--)
	{
		if (expstr->ops[expstr->i] == EXPOP_COPY)
			*(word++) = expstr->str[expstr->i];
		expstr->i++;
	}
	*word = '\0';
}
