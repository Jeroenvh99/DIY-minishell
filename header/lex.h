/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:58:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 15:28:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "ft_list.h"

# define STR_PIPE		"|"
# define STR_INPUT		"<"
# define STR_OUTPUT		">"
# define STR_HEREDOC	"<<"
# define STR_OUTPUT_APP	">>"
# define CHR_SQUOTE		'\''
# define CHR_DQUOTE		'\"'
# define CHR_VAR		'$'

t_list	*lex(char const *line);
char	*lex_tokenize(char const **str);

#endif
