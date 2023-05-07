#ifndef MSH_VAR_H
# define MSH_VAR_H

# include "ft_hash.h"

char	*var_search(char const *name, t_hashtable *locvars);
char	*var_set(char const *name, char *value, t_hashtable *locvars);
char	*var_unset(char const *name, t_hashtable *locvars);

#endif
