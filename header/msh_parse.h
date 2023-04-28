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
	TOK_STDOUT,
	TOK_HEREDOC,
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

typedef enum e_parsefunc_i {
	PARSE_CMD,
	PARSE_IO,
	N_PARSEFUNC,
}	t_parsefunc_i;

typedef struct s_token {
	char 		*str;
	t_toktype	type;
}	t_token;

typedef t_errno	(*t_parsefunc)(void *arg, size_t i);

t_errno	parse_cmd(t_list **tokens, t_list **cmds);
t_errno	parse_io(void *arg, size_t i);

t_token	*token_init(char *str, t_toktype type);
void	token_free(t_token *token);
void	token_destroy(t_token **token);

t_errno	lex(t_list **token_list, char const *line);
t_errno	token_complete(t_token *token, char const **str);
t_token	*token_get_word(char const **str);
t_token	*token_get_qword(char const **str, t_toktype type);
t_token	*token_get_meta(char const **str);

bool	is_metachr(char c);

#endif
