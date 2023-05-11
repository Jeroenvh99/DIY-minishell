/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_expand.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:46:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 15:58:20 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXPAND_H
# define MSH_EXPAND_H

# include "msh.h"
# include "msh_error.h"

# include "ft_hash.h"
# include "ft_list.h"
# include <stddef.h>

/* Expander operations.*/
typedef char	t_expop;
enum e_expop {
	EXPOP_ENDP = 0,
	EXPOP_ENDW,
	EXPOP_COPY,
	EXPOP_SKIP,
	EXPOP_ESC,
};

typedef enum e_specvar {
	SPECVAR_NONE = 0,
	SPECVAR_POS1,
	SPECVAR_POS2,
	SPECVAR_NPARAM,
	SPECVAR_EXIT,
	SPECVAR_OPTS,
	SPECVAR_SHPID,
	SPECVAR_BGPID,
	SPECVAR_SHNAME,
	N_SPECVAR,
}	t_specvar;

# define SPECVARS	"\0@*#?-$!0"

typedef struct s_expstr {
	char	*str;
	t_expop	*ops;
	size_t	i;
}	t_expstr;

typedef t_errno	(*t_expf)(t_expstr *, size_t *, t_msh *);

// Expander functions.
t_errno	expand(t_list **words, t_msh *msh);
t_errno	expand_fieldsplit(t_expstr *expstr, t_list **words);
t_errno	expand_dollar(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_var(t_expstr *expstr, size_t *exp_len, t_msh *vars);
t_errno	expand_spec_pos1(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_pos2(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_nparam(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_exit(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_opts(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_shpid(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_bgpid(t_expstr *expstr, size_t *exp_len, t_msh *msh);
t_errno	expand_spec_shname(t_expstr *expstr, size_t *exp_len, t_msh *msh);
//t_errno	expand_wildcard(t_expstr *expstr, t_msh *msh);

// Miscellaneous functions.
t_errno	expstr_resize(t_expstr *expstr, size_t name_len, char const *exp,
		size_t exp_len);

#endif
