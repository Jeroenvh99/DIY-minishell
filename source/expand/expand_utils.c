/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:39 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 15:39:40 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

t_errno	expstr_resize(t_expstr *expstr, size_t name_len, char const *exp,
		size_t exp_len)
{
	size_t const	nsize = ft_strlen(expstr->str) + exp_len - name_len + 1;
	char *const		nstr = malloc(nsize * sizeof(char));
	t_expop *const	nops = malloc(nsize * sizeof(t_expop));

	if (nstr == NULL || nops == NULL)
		return (free(nstr), free(nops), MSH_MEMFAIL);
	ft_memcpy(nstr, expstr->str, expstr->i);
	nstr[expstr->i] = '\0';
	ft_memcpy(nops, expstr->ops, expstr->i);
	nops[expstr->i] = EXPOP_ENDP;
	if (exp)
		ft_strlcat(nstr, exp, nsize);
	ft_strlcat(nstr, &expstr->str[expstr->i + name_len + 1], nsize);
	free(expstr->str);
	free(expstr->ops);
	expstr->str = nstr;
	expstr->ops = nops;
	return (MSH_SUCCESS);
}
