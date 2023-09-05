/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_syntax.h                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 13:24:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 12:54:36 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SYNTAX_H
# define MSH_SYNTAX_H

enum e_syntax_error {
	SYNTAX_SUCCESS = 0,
	SYNTAX_NONFATAL,
	SYNTAX_FATAL,
};

enum e_params {
	QUOTE = 0,
	OPERATOR,
	PARNS,
	N_PARAMS,
};

// Main functions.
int	syntax(char const *str, int params[N_PARAMS]);
int	syntax_process(char const **str, int *last, int params[N_PARAMS]);

#endif
