/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_var.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/01 15:51:02 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_VAR_H
# define MSH_VAR_H

# include "msh.h"
# include "msh_error.h"
# include "ft_hash.h"

enum e_varstr {
	VAR_ASSIGN = 0,
	VAR_APPEND,
	VAR_INVALID,
};

/* Variable functions. */
char	*var_search(char const *name, t_msh *msh);
char	*var_set(char const *name, char *value, t_hashtable *vars);
char	*var_unset(char const *name, t_hashtable *vars);

/* Utility functions. */
t_errno	var_parse(char **name, char const *entry);
int		var_isname(char const *str);

#endif
