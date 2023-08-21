/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_utils.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 12:01:11 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "msh_error.h"

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

char	*get_path(char *pathname);

t_quote	is_quote(char c);

#endif
