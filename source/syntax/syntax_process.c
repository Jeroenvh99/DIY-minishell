/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_process.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:09:23 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 16:28:43 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static inline int	process_meta(char const **str, int *l, int ps[N_PARAMS]);
static inline int	check_meta(char const **str, int *l, int ps[N_PARAMS]);
static inline int	process_word(char const **str, int *l, int ps[N_PARAMS]);
static inline int	process_quote(char c, int *quotes);

int	syntax_process(char const **str, int *last, int params[N_PARAMS])
{
	if (ft_strchr(METACHRS, **str))
		return (process_meta(str, last, params));
	return (process_word(str, last, params));
	if (syntax_process_quote(**str, &params[QUOTE]))
		*str++;
}

static inline int	process_meta(char const **str, int *l, int ps[N_PARAMS]);
{
	char const *const	toks[N_TOK_META] = {
		TOK_STDIN_STR, TOK_HEREDOC_STR,
		TOK_STDOUT_STR, TOK_STDOUT_APPEND_STR,
		TOK_PIPE_STR,
		TOK_AND_STR, TOK_OR_STR,
		TOK_OPENPAR_STR, TOK_CLOSEPAR_STR};
	size_t const		toks_len[N_TOK_META] = {1, 2, 1, 2, 1, 2, 2, 1, 1};
	int					type;

	type = N_TOK_META;
	while (type--)
}

static inline int	check_meta(char const **str, int *l, int ps[N_PARAMS])
{

}

static inline int	process_word(char const **str, int *l, int ps[N_PARAMS])
{

}

static inline int	process_quote(char c, int *quotes)
{
	if (*quotes == NOQUOTE)
	{
		if (c == '\'')
		{
			quotes = SQUOTE;
			return (1);
		}
		else if (c == '\"')
		{
			quotes = DQUOTE;
			return (1);
		}
	}
	else if ((*quotes == SQUOTE && c == '\'')
			|| (*quotes == DQUOTE && c == '\"'))
	{
		*quotes = NOQUOTE;
		return (1);
	}
	return (0);
}
