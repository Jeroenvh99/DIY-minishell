/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_var.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 15:39:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 15:31:42 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expand.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_var.h"

#include "ft_ctype.h"
#include "ft_hash.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static inline size_t	get_varname(char **name, char *str);

t_errno	expand_dollar(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	t_specvar			id;
	char const *const	specvars = SPECVARS;
	t_expf const		expfs[N_SPECVAR] = {
		expand_var,
		expand_spec_pos1, expand_spec_pos2, expand_spec_nparam,
		expand_spec_exit, expand_spec_opts, expand_spec_shpid,
		expand_spec_bgpid, expand_spec_shname};

	id = N_SPECVAR;
	while (specvars[--id])
	{
		if (specvars[id] == expstr->str[expstr->i + 1])
			break ;
	}
	return (expfs[id](expstr, exp_len, msh));
}

t_errno	expand_var(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	char	*name;
	size_t	name_len;
	char	*exp;

	name_len = get_varname(&name, &expstr->str[expstr->i + 1]);
	if (name == NULL)
		return (MSH_MEMFAIL);
	if (ft_strlen(name) == 0)
		return (expstr_resize(expstr, name_len, "$", ++*exp_len));
	exp = var_search(name, msh);
	*exp_len += ft_strlen(exp);
	free(name);
	return (expstr_resize(expstr, name_len, exp, *exp_len));
}

static inline size_t	get_varname(char **name, char *str)
{
	size_t	name_len;

	name_len = 0;
	while (ft_isalnum(str[name_len]) || str[name_len] == '_')
		name_len++;
	*name = ft_substr(str, 0, name_len);
	return (name_len);
}
