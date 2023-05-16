/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_spec_opts.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:24 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 15:39:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh.h"

#include "ft_string.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

t_errno	expand_spec_opts(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	char	*exp;
	t_errno	errno;

	exp = ft_itoa(msh->exit);
	if (exp == NULL)
		return (MSH_MEMFAIL);
	*exp_len += ft_strlen(exp);
	errno = expstr_resize(expstr, 1, exp, *exp_len);
	free(exp);
	return (errno);
}
