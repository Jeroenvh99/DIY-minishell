#ifndef MSH_VAR_H
# define MSH_VAR_H

# include "msh.h"
# include "msh_error.h"
# include "ft_hash.h"

# define CHR_VAR_ASSIGN	'='

char	*var_search(char const *name, t_msh *msh);
char	*var_set(char const *name, char *value, t_hashtable *vars);
char	*var_unset(char const *name, t_hashtable *vars);

t_errno	var_parse(char **name, char **value, char const *entry);

#endif
