/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_syntax.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:24:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/14 16:56:48 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SYNTAX_H
# define MSH_SYNTAX_H

# include "msh_parse.h"
# include "ft_list.h"

enum e_cat {
	NONE = -1,
	WORD = 0,
	REDIRECT,
	PIPE,
	OPERATOR,
	PARENTHESIS,
	N_CAT,
};

enum e_synterror {
	SUCCESS = 0,
	SYNTERROR_FATAL,
	SYNTERROR_PIPE,
	SYNTERROR_OPERATOR,
	SYNTERROR_PARENTHESIS,
	N_SYNTERROR,
};

typedef int	(*t_action)(int*, int*);

// Main functions.
int	syntax_check(t_list *tokens);

// Actions.
int	syntax_check_word(int *last, int *pars);
int	syntax_check_redir(int *last, int *pars);
int	syntax_check_pipe(int *last, int *pars);
int	syntax_check_operator(int *last, int *pars);
int	syntax_check_openpar(int *last, int *pars);
int	syntax_check_closepar(int *last, int *pars);

#endif
