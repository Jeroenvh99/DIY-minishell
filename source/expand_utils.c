#include "msh_expand.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

t_errno	ft_strexp(char **str, size_t slot_i, size_t slot_len, char const *subst)
{
	char			*nstr;
	size_t const	nstr_size = ft_strlen(*str) + ft_strlen(subst) - slot_len + 1;
	
	printf("%zu\n%zu\n%zu\n%zu\n", ft_strlen(*str), ft_strlen(subst), slot_len, nstr_size);
	nstr = malloc(nstr_size * sizeof(char));
	if (nstr == NULL)
		return (MSH_MEMFAIL);
	ft_memcpy(nstr, *str, slot_i);
	nstr[slot_i] = '\0';
	if (subst)
		ft_strlcat(nstr, subst, nstr_size);
	ft_strlcat(nstr, &(*str)[slot_i + slot_len], nstr_size);
	free(*str);
	*str = nstr;
	return (MSH_SUCCESS);
}
