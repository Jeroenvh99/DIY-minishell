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
	
static inline char		*get_varname(char *str, size_t *name_len);
static inline t_errno	expstr_resize(t_expstr *expstr, size_t name_len, char const *exp, size_t exp_len);

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

	name = get_varname(&expstr->str[expstr->i + 1], &name_len);
	if (name == NULL)
		return (MSH_MEMFAIL);
	exp = var_search(name, msh->var);
	*exp_len += ft_strlen(exp) - 1;
	free(name);
	return (expstr_resize(expstr, name_len + 1, exp, *exp_len));
}

static inline t_errno	expstr_resize(t_expstr *expstr, size_t name_len,
							char const *exp, size_t exp_len)
{
	size_t const	nsize = ft_strlen(expstr->str) + exp_len - name_len + 1;
	char *const		nstr = malloc(nsize * sizeof(char));
	t_expop	*const	nops = malloc(nsize * sizeof(t_expop));
	
	if (nstr == NULL || nops == NULL)
		return (free(nstr), free(nops), MSH_MEMFAIL);
	ft_memcpy(nstr, expstr->str, expstr->i);
	nstr[expstr->i] = '\0';
	ft_memcpy(nops, expstr->ops, expstr->i);
	nops[expstr->i] = EXPOP_ENDP;
	if (exp)
		ft_strlcat(nstr, exp, nsize);	
	ft_strlcat(nstr, &expstr->str[expstr->i + name_len], nsize);
	free(expstr->str);
	free(expstr->ops);
	expstr->str = nstr;
	expstr->ops = nops;
	return (MSH_SUCCESS);
}
	

static inline char	*get_varname(char *str, size_t *name_len)
{
	*name_len = 0;
	while (ft_isalnum(str[*name_len]) || str[*name_len] == '_')
		(*name_len)++;
	return (ft_substr(str, 0, *name_len));
}
