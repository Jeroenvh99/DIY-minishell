/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_home.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:10 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 15:49:37 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh_error.h"
#include "msh.h"

#include "ft_string.h"
#include <stdlib.h>

t_errno	expand_home(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	char const	*exp;

	if (var_search(&exp, "HOME", msh) != MSH_SUCCESS)
		return (MSH_MEMFAIL);
	*exp_len += ft_strlen(exp);
	return (expstr_resize(expstr, 1, exp, *exp_len));
}
