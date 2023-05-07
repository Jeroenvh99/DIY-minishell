#include "msh_var.h"

#include "ft_hash.h"
#include <stdlib.h>

char	*var_search(char const *name, t_hashtable *locvars)
{
	char	*value;

	if (!locvars)
		return (getenv(name));
	value = hashtable_search(locvars, name);
	if (value == NULL)
		value = getenv(name);
	return (value);
}
