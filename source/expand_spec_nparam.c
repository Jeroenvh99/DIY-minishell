#include "msh_expand.h"
#include "msh.h"

#include "ft_string.h"
#include "ft_stdlib.h"
#include <stddef.h>
#include <stdlib.h>

t_errno	expand_spec_nparam(t_expstr *expstr, size_t *exp_len, t_msh *msh)
{
	char	*exp;
	t_errno	errno;

	exp = ft_itoa(msh->exit);
	if (exp == NULL)
		return (MSH_MEMFAIL);
	errno = ft_strexp(&expstr->str, expstr->i, 1, exp);
	*exp_len += ft_strlen(exp);
	free(exp);
	return (errno);
}
