/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_utils.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/28 14:25:35 by jvan-hal      ########   odam.nl         */
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

# define CHR_DIRSEP		47
# define CHR_SQUOTE		39
# define CHR_DQUOTE		34
# define CHR_VAR		36
# define CHR_WILDCARD	42

char	*get_path(char *pathname);

t_quote	is_quote(char c);

#endif
