/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_token.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:37:03 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/05 11:32:29 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TOKEN_H
# define MSH_TOKEN_H

# include <stddef.h>

/* TOK_TRUNC varieties are equal to the negative of the corresponding e_quote
 * value.
 */
enum e_toktype {
	TOK_TRUNC_DQUOTE = -2,
	TOK_TRUNC = -1,
	TOK_NONE = 0,
	TOK_WORD,
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
};

# define TOK_ARG_MIN			1 // First command argument token (TOK_WORD).
# define N_TOK_ARG				5 // Tokens to pass as command arguments.
# define TOK_META_MIN			2 // First non-word token (TOK_STDIN).
# define N_TOK_META				9 // Non-word tokens.
# define TOK_CTL_MIN			7 // First control flow token (TOK_AND).
# define N_TOK_CTL				4 // Tokens to determine control flow.

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

typedef struct s_token	t_token;

/* Token object.
 * @param str	If the token is a word: the word.
 * @param type	The token's type.
 */
struct s_token {
	char	*str;
	int		type;
};

// Token functions.
t_token	*token_init(char *str, int type);
void	token_free(t_token *token);
void	token_destroy(t_token **token);

int		token_read(char const *str, size_t *len);
int		token_read_meta(char const *str, size_t *len);
int		token_read_word(char const *str, size_t *len, int *quote);

int		token_is_andor(int type);
int		token_is_parenthesis(int type);
int		token_is_redirection(int type);
int		token_is_unclosed(int type);

// Miscellaneous functions.
int		is_argtok(t_token const *token);
int		is_ctltok(t_token const *token);
char	*token_to_str(t_token *token);

#endif
