/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_prompt.h                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 13:23:53 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 11:42:38 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PROMPT_H
# define MSH_PROMPT_H

# include "msh.h"

# define PROMPT			"msh$ "
# define PROMPT_CONT	"> "
# define PROMPT_PIPE	" pipe"
# define PROMPT_QUOTE	" quote"
# define PROMPT_SQUOTE	" squote"
# define PROMPT_DQUOTE	" dquote" 
# define PROMPT_PAR		" parenthesis"
# define PROMPT_CMDAND	" cmdand"
# define PROMPT_CMDOR	" cmdor"
# define PROMPT_HEREDOC	"heredoc"

enum e_exstat {
	IACTV_SUCCESS = 0,
	IACTV_FAIL,
	IACTV_INTERRUPT,
	IACTV_TERM,
	IACTV_EOF,
	N_IACTV_EXIT,
	IACTV_FAIL_0,
};

typedef void	(*t_promptf)(t_fd, char const*, t_msh*);

int		prompt(t_promptf promptf, t_fd outf, char const *delim, t_msh *msh);

void	cmdline(t_fd outf, char const *delim, t_msh *msh);
void	heredoc(t_fd outf, char const *delim, t_msh *msh);

#endif
