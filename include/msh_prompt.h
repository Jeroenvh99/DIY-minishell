/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_prompt.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 13:23:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/29 14:14:33 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PROMPT_H
# define MSH_PROMPT_H

# define PROMPT			"msh$ "
# define PROMPT_CONT	"> "
# define PROMPT_PIPE	"pipe"
# define PROMPT_QUOTE	"quote"
# define PROMPT_SQUOTE	"squote"
# define PROMPT_DQUOTE	"dquote"
# define PROMPT_PAR		"parenthesis"
# define PROMPT_CMD		"cmd"
# define PROMPT_HEREDOC	"heredoc"

enum e_exstat {
	IACTV_SUCCESS = 0,
	IACTV_FAILED,
	IACTV_SIGNALED,
	IACTV_TERMINATED,
	IACTV_EOF,
};

#endif
