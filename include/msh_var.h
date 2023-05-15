#ifndef MSH_VAR_H
# define MSH_VAR_H

# include "msh_error.h"
# include "ft_hash.h"

t_errno	var_search(char **value, char const *name, t_msh *msh);
//char	*var_set(char const *name, char *value, t_hashtable *locvars);
//char	*var_unset(char const *name, t_hashtable *locvars);

#endif
