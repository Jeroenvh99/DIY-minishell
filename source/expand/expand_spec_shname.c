/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_spec_shname.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:35 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/03 22:12:13 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh.h"

#include "ft_string.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

t_errno	expand_spec_shname(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	char const *const	exp = "msh";
	t_errno				errno;

	(void) msh;
	*exp_len += ft_strlen(exp);
	errno = expstr_resize(expstr, 1, exp, *exp_len);
	return (errno);
}
