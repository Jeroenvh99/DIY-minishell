/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_in.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:56:28 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

#include "ft_list.h"
#include <stdlib.h>

static inline t_errno	input_configure(t_list **tokens, t_cmd *cmd);

t_errno	parse_input(t_list **tokens, t_list **cmds)
{
	t_cmd	*cmd;

	cmd = cmd_get_current(*cmds);
	cmd->io.in_mode = IN_REDIRECT;
	return (input_configure(tokens, cmd));
}

t_errno	parse_heredoc(t_list **tokens, t_list **cmds)
{
	t_cmd	*cmd;

	cmd = cmd_get_current(*cmds);
	cmd->io.in_mode = IN_HEREDOC;
	return (input_configure(tokens, cmd));
}

static inline t_errno	input_configure(t_list **tokens, t_cmd *cmd)
{
	t_token	*word;

	free(token_pop(tokens));
	word = token_pop(tokens);
	if (!word || word->type == TOK_INVALID || word->type >= TOK_META_MIN)
		return (token_destroy(&word), MSH_SYNTAX_ERROR);
	free(cmd->io.in);
	cmd->io.in = word->str;
	free(word);
	return (MSH_SUCCESS);
}
