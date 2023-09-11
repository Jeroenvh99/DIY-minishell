/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_var.h                                          :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/11 15:36:29 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_VAR_H
# define MSH_VAR_H

# include "msh.h"
# include "ft_hash.h"

enum e_varstat {
	VAR_NOVAR = 0,
	VAR_ASSIGN,
	VAR_APPEND,
	VAR_INVID,
};

/* Variable functions. */
char	*var_search(char const *name, t_msh *msh);
char	*var_set(char const *name, char *value, t_hashtable *vars);
char	*var_unset(char const *name, t_hashtable *vars);

/* Utility functions. */
int		var_parse(char **name, char const *entry);
int		var_isname(char const *str);

#endif
