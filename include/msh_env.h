/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_env.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:13 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/03 14:26:58 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
t_errno	env_append_val(t_env *env, char *entry, char const *name);
int		env_update(t_env *env, char const *name, char const *value);
t_errno	env_unset(t_env *env, char const *name);
char	*env_search(t_env *env, char const *name);

// Utility functions.
size_t	env_entry_get(t_env *env, char const *name);
char	*env_entry_getval(char const *entry, char const *name);
void	env_pack(t_env *env);
char	**copy_env(char **env);
int		env_size(char **env);
void	print_2d_arr(int fd, char **arr, size_t size);
void	print_error(char *command, char *argument, char *message);
t_errno	get_env_var(char *name, char **value, char **env);
int		remove_var(char *name, char **env);

#endif
