/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_parse.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 13:46:33 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 12:22:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSE_H
# define MSH_PARSE_H

# include "msh.h"
# include "msh_error.h"

# include "ft_list.h"
# include <stddef.h>

/* TOK_TRUNC varieties are equal to the negative of the corresponding e_quote
 * value.
 */
typedef enum e_toktype {
	TOK_TRUNC_DQUOTE = -2,
	TOK_TRUNC = -1,
	TOK_WORD = 0,
	TOK_STDIN,
	TOK_HEREDOC,
	TOK_STDOUT,
	TOK_STDOUT_APPEND,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_OPENPAR,
	TOK_CLOSEPAR,
	TOK_INVALID,
	N_TOK,
}	t_toktype;

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

enum e_pipeends {
	PIPE_READ = 0,
	PIPE_WRITE,
};

enum e_tunion_tags {
	TAG_PPL = 0,
	TAG_CTL,
};

# define N_TOK_ARG				5 /* Tokens to pass as command arguments. */
# define TOK_META_MIN			1 /* The first non-word token (TOK_STDIN). */
# define N_TOK_META				9 /* Non-word tokens. */
# define TOK_CTL_MIN			6 /* The first control flow token (TOK_AND). */
# define N_TOK_CTL				4 /* Tokens to determine control flow. */

# define TOK_STDIN_STR			"<"
# define TOK_STDOUT_STR			">"
# define TOK_HEREDOC_STR		"<<"
# define TOK_STDOUT_APPEND_STR	">>"
# define TOK_PIPE_STR			"|"
# define TOK_AND_STR			"&&"
# define TOK_OR_STR				"||"
# define TOK_OPENPAR_STR		"("
# define TOK_CLOSEPAR_STR		")"

# define METACHARS				"|&<>() \t\n"

typedef struct s_tunion	t_tunion;
typedef struct s_token	t_token;

typedef t_errno			(*t_argparsef)(t_cmd *, t_list **, t_msh *);

/* Token object.
 * @param str	If the token is a word: the word.
 * @param type	The token's type.
 */
struct s_token {
	char		*str;
	t_toktype	type;
};

/* Parser's tagged union object.
 * @param tag	Tag.
 * @param data	Memory pointer (to either a single pipeline or a control token).
 */
struct s_tunion {
	int		tag;
	union	u_token {
		t_list	*ppl;
		t_token	*ctl;
	}	data;
};

// Token functions.
t_token	*token_init(char *str, t_toktype type);
void	token_free(t_token *token);
void	token_destroy(t_token **token);

// Lexer functions.
t_errno	lex(t_list **tokens, char const *line);
t_errno	token_complete(t_token *token, char const **str);
t_token	*token_get_word(char const **str);
t_token	*token_get_meta(char const **str);

// Parser functions.
t_errno	parse(t_msh *msh, t_list **tokens);
t_errno	parse_pipeline(t_list **pipeline, t_list **tokens, t_msh *msh);
t_errno	parse_cmd(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_pipe(t_fd *out, t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_word(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_input(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_heredoc(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_output(t_cmd *cmd, t_list **tokens, t_msh *msh);
t_errno	parse_output_append(t_cmd *cmd, t_list **tokens, t_msh *msh);

t_errno	ft_shuntingyard(t_list **out, t_list **in, t_msh *msh);

//t_errno	parse_and(t_cmdtree *tree, t_list **tokens, t_msh *msh);
//t_errno	parse_or(t_cmdtree *tree, t_list **tokens, t_msh *msh);

t_errno	parse_iofile(char **name, t_list **tokens, t_msh *msh);

// Miscellaneous functions.
int		is_argtok(t_token const *token);
int		is_ctltok(t_token const *token);
int		is_metachr(char c);
char	*token_to_str(t_token *token);
void	tunion_free(void *ptr);

#endif
