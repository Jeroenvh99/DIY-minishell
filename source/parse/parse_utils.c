/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 11:50:28 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/15 17:09:47 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_expand.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

t_cmd	*cmd_get_current(t_list *cmds)
{
	t_list	*cmd_node;

	cmd_node = list_last(cmds);
	if (!cmd_node)
		return (NULL);
	return ((t_cmd *)cmd_node->content);
}

t_errno	parse_iofile(char **name, t_list **tokens, t_msh *msh)
{
	char	*str;
	t_list	*words;

	str = token_to_str(list_pop_ptr(tokens));
	if (!str)
		return (MSH_SYNTAX_ERROR);
	words = NULL;
	if (expand(&words, &str, msh) != MSH_SUCCESS)
		return (list_clear(&words, free), free(str), MSH_MEMFAIL);
	if (words->next)
		return (list_clear(&words, free), MSH_SYNTAX_ERROR);
	*name = words->content;
	list_clear(&words, NULL);
	return (MSH_SUCCESS);
}

char	*token_to_str(t_token *token)
{
	char	*str;

	if (!token)
		return (NULL);
	str = token->str;
	free(token);
	return (str);
}
