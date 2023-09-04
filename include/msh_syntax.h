/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_syntax.h                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:24:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 00:11:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SYNTAX_H
# define MSH_SYNTAX_H

# include "msh_parse.h"
# include "ft_list.h"

enum e_syntax_error {
	SYNTAX_SUCCESS = 0,
	SYNTAX_NONFATAL,
	SYNTAX_FATAL,
};

enum e_tokcat {
	NONE = -1,
	WORD = 0,
	REDIRECT,
	PIPE,
	T_OPERATOR,
	PARENTHESIS,
	N_CAT,
};

enum e_params {
	QUOTE = 0,
	OPERATOR,
	PARNS,
	N_PARAMS,
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
int syntax(char const *str, int params[N_PARAMS]);
int	syntax_process(char const **str, int *last, int params[N_PARAMS]);

// Actions.
int	syntax_check_word(int *last, int *pars);
int	syntax_check_redir(int *last, int *pars);
int	syntax_check_pipe(int *last, int *pars);
int	syntax_check_operator(int *last, int *pars);
int	syntax_check_openpar(int *last, int *pars);
int	syntax_check_closepar(int *last, int *pars);

#endif
