/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_parse.h                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:46:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 11:30:05 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include "msh.h"
# include "msh_error.h"
# include "msh_token.h"

# include "ft_list.h"
# include <stddef.h>

enum e_in_mode {
	IN_STD,
	IN_REDIRECT,
	IN_HEREDOC,
	N_IN_MODE,
};

enum e_out_mode {
	OUT_STD,
	OUT_REDIRECT,
	OUT_APPEND,
	N_OUT_MODE,
};

typedef t_errno	(*t_argparsef)(t_cmd *, t_list **, t_msh *);

// Lexer functions.
t_errno	lex(t_list **tokens, char const *line);
t_errno	token_complete(t_token *token, char const **str);
t_token	*token_get_word(char const **str);
t_token	*token_get_meta(char const **str);

// Parser functions.
t_errno	parse(t_msh *msh, t_list **tokens);
t_errno	parse_cmdtree(t_cmdtree **tree, t_list **tokens, t_msh *msh);
t_errno	parse_pipeline(t_list **pipeline, t_list **tokens, t_msh *msh);
t_errno	parse_cmd(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_word(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_input(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_heredoc(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_output(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_output_append(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_invalid(t_cmd *cmd, t_list **tokens, t_msh *msh);

t_errno	parse_iofile(char **name, t_list **tokens, t_msh *msh);
t_errno	parse_pipe(t_cmd *cmd, t_list **tokens, t_msh *msh);

#endif
