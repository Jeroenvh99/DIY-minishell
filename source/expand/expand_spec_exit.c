/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_spec_exit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/28 15:21:42 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh.h"

#include "ft_string.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

t_errno	expand_spec_exit(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	char *const	exp = ft_itoa(msh->exit);
	t_errno		errno;

	if (!exp)
		return (MSH_MEMFAIL);
	*exp_len += ft_strlen(exp);
	errno = expstr_resize(expstr, 1, exp, *exp_len);
	free(exp);
	return (errno);
}
