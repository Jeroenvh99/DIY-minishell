/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_utils.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/22 08:44:15 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "msh_error.h"
# include "ft_list.h"

typedef enum e_quote {
	NOQUOTE = 0,
	SQUOTE,
	DQUOTE,
	N_QUOTES,
}	t_quote;

# define CHR_DIRSEP		'/'
# define CHR_SQUOTE		'\''
# define CHR_DQUOTE		'\"'
# define CHR_VAR		'$'
# define CHR_WILDCARD	'*'

typedef void	(*t_freef)(void *);

char	*get_path(char *pathname);

t_quote	is_quote(char c);

/* List functions. */
t_errno	list_append_ptr(t_list **lst, void *ptr);
t_list	*list_pop(t_list **lst);
void	*list_pop_ptr(t_list **lst);
t_errno	list_push_ptr(t_list **lst, void *ptr);

#endif
