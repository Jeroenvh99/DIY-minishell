/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_string.h"

t_errno	parse(t_list **tokens, t_list **cmds)
{
	t_parsefunc const	parsefuncs[N_TOK] = {
		parse_cmd, parse_cmd,
		parse_meta_pipe,
		parse_meta_input, parse_meta_heredoc,
		parse_meta_output, parse_meta_output_append,
		parse_and, parse_or};
	t_errno				errno;

	errno = MSH_SUCCESS;
	while (*tokens)
	{
		errno = parsefuncs[((*tokens)->content)->type](tokens, cmds);
		if (errno != MSH_SUCCESS)
			break ;
	}
	return (errno);
}

/*
t_errno	parse_grammar(t_list *tokens)
{
	t_toktype	type;
	t_toktype	prevtype;

	prevtype = TOK_INVALID;
	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		prevtype = type;
		tokens = tokens->next;
	}
	return (MSH_SUCCESS);
}*/
