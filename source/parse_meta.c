/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_meta.c                                       :+:    :+:            */
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

#include <stdlib.h>

static inline void	process_node(t_list **token_list);

t_errno	parse_meta_pipe(t_list **token_list, t_cmdtable *cmdtable)
{
	t_list	*node;
	t_token	*token;

	node = *token_list;
	token = (*token_list)->content;
	return (MSH_SUCCESS);
}

t_errno	parse_meta_input(t_list **token_list, t_cmdtable *cmdtable)
{
	t_token	*word;

	process_node(token_list);
	word = (*token_list)->content;
	if (word->type == TOK_INVALID || word->type >= TOK_META_MIN)
		return (MSH_SYNTAX_ERROR);
	free(cmdtable->io.in);
	cmdtable->io.in_mode = IN_REDIRECT;
	cmdtable->io.in = word->str;
	process_node(token_list);
	return (MSH_SUCCESS);
}

t_errno	parse_meta_output(t_list **token_list, t_cmdtable *cmdtable)
{
	t_token	*word;

	process_node(token_list);
	word = (*token_list)->content;
	if (word->type == TOK_INVALID || word->type >= TOK_META_MIN)
		return (MSH_SYNTAX_ERROR);
	free(cmdtable->io.out);
	cmdtable->io.out_mode = OUT_REDIRECT;
	cmdtable->io.out = word->str;
	process_node(token_list);
	return (MSH_SUCCESS);
}

t_errno	parse_meta_heredoc(t_list **token_list, t_cmdtable *cmdtable)
{
	t_errno	errno;
	
	errno = parse_meta_input(token_list, cmdtable);
	cmdtable->io.in_mode = IN_HEREDOC;
	return (errno);
}

t_errno	parse_meta_output_append(t_list **token_list, t_cmdtable *cmdtable)
{
	t_errno	errno;
	
	errno = parse_meta_input(token_list, cmdtable);
	cmdtable->io.out_mode = OUT_APPEND;
	return (errno);
}

static inline void	process_node(t_list **token_list)
{
	t_list	*node;

	node = *token_list;
	*token_list = node->next;
	list_delete(node, free);
}
