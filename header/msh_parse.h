/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_parse.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:46:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 13:58:50 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include "msh_error.h"

# include "ft_list.h"
# include <stddef.h>

# define TOK_PIPE			"|"
# define TOK_STDIN			"<"
# define TOK_STDOUT			">"
# define TOK_HEREDOC		"<<"
# define TOK_STDOUT_APPEND	">>"
# define TOK_AND			"&&"
# define TOK_OR				"||"
# define N_METATOK			7

# define CHR_SQUOTE			'\''
# define CHR_DQUOTE			'\"'
# define CHR_VAR			'$'
# define CHR_WILDCARD		'*'

typedef enum e_parsefunc_i {
	PARSE_CMD,
	PARSE_IO,
	N_PARSEFUNC,
}	t_parsefunc_i;

typedef t_errno	(*t_parsefunc)(void *arg, size_t i);

t_errno	parse_cmd(void *arg, size_t i);
t_errno	parse_io(void *arg, size_t i);

#endif
