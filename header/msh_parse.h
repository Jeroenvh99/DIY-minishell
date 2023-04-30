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
# include <stdbool.h>
# include <stddef.h>

typedef enum e_toktype {
	TOK_QWORD_TRUNC = -2,
	TOK_WORD_TRUNC = -1,
	TOK_INVALID = 0,
	TOK_WORD,
	TOK_QWORD,
	TOK_PIPE,
	TOK_STDIN,
	TOK_HEREDOC,
	TOK_STDOUT,
	TOK_STDOUT_APPEND,
	TOK_AND,
	TOK_OR,
	N_TOK,
}	t_toktype;

# define TOK_META_MIN			3
# define N_TOK_META				7

# define TOK_PIPE_STR			"|"
# define TOK_STDIN_STR			"<"
# define TOK_STDOUT_STR			">"
# define TOK_HEREDOC_STR		"<<"
# define TOK_STDOUT_APPEND_STR	">>"
# define TOK_AND_STR			"&&"
# define TOK_OR_STR				"||"

# define METACHARS				"|&<> \t\n"
# define CHR_DIRSEP				'/'
# define CHR_DQUOTE				'\"'
# define CHR_SQUOTE				'\''
# define CHR_VAR				'$'
# define CHR_WILDCARD			'*'

typedef struct s_token {
	char 		*str;
	t_toktype	type;
}	t_token;

//typedef t_errno	(*t_parsefunc)(t_list **tokens, t_cmdtable *cmdtable);

// Token functions.
t_token	*token_init(char *str, t_toktype type);
void	token_free(t_token *token);
void	token_destroy(t_token **token);

// Lexer functions.
t_errno	lex(t_list **token_list, char const *line);
t_errno	token_complete(t_token *token, char const **str);
t_token	*token_get_word(char const **str);
t_token	*token_get_qword(char const **str, t_toktype type);
t_token	*token_get_meta(char const **str);

/*// Parser functions.
t_errno	parse(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_cmd(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_meta_pipe(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_meta_input(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_meta_heredoc(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_meta_output(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_meta_output_append(t_list **tokens, t_cmdtable *cmdtable);
t_errno	parse_meta_and(t_list **tokens, t_cmdtable *cmdtable);
t_errno parse_meta_or(t_list **tokens, t_cmdtable *cmdtable);
*/
// Miscellaneous functions.
bool	is_metachr(char c);

#endif
