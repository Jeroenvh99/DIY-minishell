/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 13:58:40 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_string.h"

t_errno	parse(t_msh *msh, t_list **tokens)
{
	t_list	**pipeline;
	t_errno	errno;

	pipeline = &msh->cmds;
	while (*tokens)
	{
		if (!is_ctltok((*tokens)->content))
			errno = parse_pipeline(pipeline, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (errno);
	}
	return (MSH_SUCCESS);
}

t_errno	parse_pipeline(t_list **pipeline, t_list **tokens, t_msh *msh)
{
	t_errno	errno;
	t_cmd	*cmd;

	while (*tokens && !is_ctltok((*tokens)->content))
	{
		cmd = cmd_init(0, NULL);
		if (cmd == NULL)
			return (MSH_MEMFAIL);
		errno = parse_cmd(cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
		errno = list_append_ptr(pipeline, cmd);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), cmd_free(cmd),
				errno);
		errno = parse_pipe(cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(pipeline, (t_freef)cmd_free), errno);
	}
	return (MSH_SUCCESS);
}

t_errno	parse_cmd(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	t_toktype			type;
	t_argparsef const	argparsefs[N_TOK_ARG] = {
		parse_word,
		parse_input, parse_heredoc,
		parse_output, parse_output_append};
	t_errno				errno;

	while (*tokens && is_argtok((*tokens)->content))
	{
		type = ((t_token *)(*tokens)->content)->type;
		errno = argparsefs[type](cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (cmd_free_list(cmd), errno);
	}
	return (cmd_finish(cmd));
}

t_errno	parse_invalid(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	(void) cmd;
	(void) tokens;
	(void) msh;
	return (MSH_SYNTAX_ERROR);
}
