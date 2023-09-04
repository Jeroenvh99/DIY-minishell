/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbasting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:58:21 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/04 14:53:23 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_token.h"

int	token_is_andor(int type)
{
	return (type == TOK_AND || type == TOK_OR);
}

int	token_is_parenthesis(int type)
{
	return (type == TOK_OPENPAR || type == TOK_CLOSEPAR);
}

int	token_is_redirection(int type)
{
	return (type == TOK_STDIN
		|| type == TOK_STDOUT
		|| type == TOK_HEREDOC
		|| type == TOK_STDOUT_APPEND);
}

int	token_is_unclosed(int type)
{
	return (type == TOK_TRUNC || type == TOK_TRUNC_DQUOTE);
}
