/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:29:41 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 16:33:05 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

int	token_type(char const *str)
{
	char const *const	metatokens[N_TOK_META] = {
		TOK_STDIN_STR, TOK_HEREDOC_STR,
		TOK_STDOUT_STR, TOK_STDOUT_APPEND_STR,
		TOK_PIPE_STR,
		TOK_AND_STR, TOK_OR_STR,
		TOK_OPENPAR_STR, TOK_CLOSEPAR_STR};
	size_t const		metatokens_len[N_TOK_META] = {
		1, 2, 1, 2, 1, 2, 2, 1, 1};
	int					type;

	type = N_TOK_META;
	while (type--)
	{
		if (!ft_strncmp(metatokens[type], *str, metatokens_len[type]))
			return (type);
	}
	return (TOK_WORD);
}
