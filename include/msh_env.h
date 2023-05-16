#ifndef MSH_ENV_H
# define MSH_ENV_H

# include "msh_error.h"
# include <stddef.h>

/* Environment object.
 * @param envp	The array of strings constituting the environment.
 * @param len	The number of indices for which space is currently allocated.
 * 				This excludes the terminating NULL pointer.
 * @param used	The number of indices which are currently in use.
 */
typedef struct s_env {
	char	**envp;
	size_t	len;
	size_t	used;
}	t_env;

// Environment functions.
t_errno	env_init(t_env *env, char **envp);
void	env_free(t_env *env);
t_errno	env_set(t_env *env, char const *entry);
void	env_unset(t_env *env, char const *name);
char	*env_search(t_env *env, char const *name);

// Utility functions.
size_t	env_entry_get(char **envp, char const *name);
char	*env_entry_getval(char const *entry, char const *name);

#endif
