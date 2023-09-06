/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_utils.h                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:43:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 12:53:17 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "msh_error.h"

# include <stddef.h>

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

char	*ft_strnjoin(char const *s1, char const *s2, size_t n);

#endif
