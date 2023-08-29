/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_syntax.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:24:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/29 16:24:36 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SYNTAX_H
# define MSH_SYNTAX_H

# include "msh_parse.h"
# include "ft_list.h"

# define CHARS	"\'\"|&()<>"

enum e_cat {
	NONE = -1,
	WORD = 0,
	REDIRECT,
	PIPE,
	OPERATOR,
	PARENTHESIS,
	N_CAT,
};

enum e_params {
	QUOTE = 0,
	CTL,
	PARNS,
	N_PARAMS,
};

enum e_quote {
	NOQUOTE = 0,
	SQUOTE,
	DQUOTE,
};

enum e_ctl {
	NOCTL = 0,
	AND,
	OR,
};

enum e_syntax_mode {
	SYNTAX_SUCCESS = 0,
	SYNTAX_FATAL,
	SYNTAX_SQUOTE,
	SYNTAX_DQUOTE,
	SYNTAX_PIPE,
	SYNTAX_CTL,
	SYNTAX_PAR,
	N_SYNTAX,
};

typedef int	(*t_action)(int*, int*);

// Main functions.
int	syntax(char const *str);
int	syntax_check(t_list *tokens);

// Actions.
int	syntax_check_word(int *last, int *pars);
int	syntax_check_redir(int *last, int *pars);
int	syntax_check_pipe(int *last, int *pars);
int	syntax_check_operator(int *last, int *pars);
int	syntax_check_openpar(int *last, int *pars);
int	syntax_check_closepar(int *last, int *pars);

#endif
