/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_lex.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:58:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 15:28:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_LEX_H
# define MSH_LEX_H

# include "ft_list.h"
# include <stdbool.h>

# define METACHARS	"|&<> \t\n"

t_list	*lex(char const *line);
char	*lex_tokenize(char const **str);
bool	is_metachr(char c);

#endif
