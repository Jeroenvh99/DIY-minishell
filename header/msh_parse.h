/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_parse.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:46:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 15:02:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include "msh_error.h"
# include "msh.h"

# include "ft_list.h"
# include <stdbool.h>
# include <stddef.h>

//TOK_TRUNC varieties are equal to the negative of the corresponding e_quote
//value.
typedef enum e_toktype {
	TOK_TRUNC_DQUOTE = -2,
	TOK_TRUNC_SQUOTE = -1,
	TOK_WORD = 0,
	TOK_PIPE,
	TOK_STDIN,
	TOK_HEREDOC,
	TOK_STDOUT,
	TOK_STDOUT_APPEND,
	TOK_AND,
	TOK_OR,
	TOK_INVALID,
	N_TOK,
}	t_toktype;

# define TOK_META_MIN			2
# define N_TOK_META				7

# define TOK_PIPE_STR			"|"
# define TOK_STDIN_STR			"<"
# define TOK_STDOUT_STR			">"
# define TOK_HEREDOC_STR		"<<"
# define TOK_STDOUT_APPEND_STR	">>"
# define TOK_AND_STR			"&&"
# define TOK_OR_STR				"||"

typedef enum e_quote {
	NOQUOTE = 0,
	SQUOTE,
	DQUOTE,
	N_QUOTES,
}	t_quote;

# define METACHARS				"|&<> \t\n"
# define CHR_DIRSEP				'/'
# define CHR_SQUOTE				'\''
# define CHR_DQUOTE				'\"'
# define CHR_VAR				'$'
# define CHR_WILDCARD			'*'

/* Token object.
 * @param str	If the token is a word: the word.
 * @param type	The token's type.
 */
typedef struct s_token {
	char 		*str;
	t_toktype	type;
}	t_token;

typedef t_errno	(*t_parsefunc)(t_list **tokens, t_list **cmds);

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

// Parser functions.
t_errno	parse(t_list **tokens, t_list **cmds);
t_errno	parse_word(t_list **tokens, t_list **cmds);
t_errno	parse_pipe(t_list **tokens, t_list **cmds);
t_errno	parse_input(t_list **tokens, t_list **cmds);
t_errno	parse_heredoc(t_list **tokens, t_list **cmds);
t_errno	parse_output(t_list **tokens, t_list **cmds);
t_errno	parse_output_append(t_list **tokens, t_list **cmds);
t_errno	parse_and(t_list **tokens, t_list **cmds);
t_errno parse_or(t_list **tokens, t_list **cmds);

t_errno	parse_add_cmd(t_list **tokens, t_list **cmds);

// Expander functions.
char	*strunquote(char *str);

// Miscellaneous functions.
bool	is_metachr(char c);
t_quote	is_quote(char c);
t_cmd	*cmd_get_current(t_list *cmds);
t_token	*token_pop(t_list **tokens);

#endif
