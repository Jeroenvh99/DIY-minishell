#include "msh_env.h"
#include "msh_error.h"

#include "ft_string.h"
#include <stdlib.h>

/*t_errno	env_set(t_env *env, char const *entry)
{
	char *const	copy = ft_strdup(entry);

	if (!copy)
		return (MSH_MEMFAIL);
	return (env_set_main(env, copy));
}*/

t_errno	env_update(t_env *env, char const *name, char const *value)
{
	char *const	entry = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	
	if (!entry)
		return (MSH_MEMFAIL);
	entry[0] = '\0';
	ft_strlcat(entry, name, -1);
	ft_strlcat(entry, "=", -1);
	ft_strlcat(entry, value, -1);
	return (env_set(env, entry));
}	
