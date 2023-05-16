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

t_errno	cmd_argvconvert(t_cmd *cmd)
{
	t_list	*argv_list;
	size_t	size;
	char	*word;

	argv_list = cmd->argv.list;
	cmd->argc = list_size(argv_list);
	size = cmd->argc + 1;
	cmd->argv.array = malloc(size * sizeof(char *));
	if (cmd->argv.array == NULL)
		return (list_clear(&argv_list, free), MSH_MEMFAIL);
	cmd->argv.array[--size] = NULL;
	while (size--)
	{
		word = list_pop_ptr(&argv_list);
		cmd->argv.array[size] = word;
	}
	return (MSH_SUCCESS);
}

t_errno	parse_iofile(char **name, t_list **tokens, t_msh *msh)
{
	char	*str;
	t_list	*words;

	str = token_to_str(list_pop_ptr(tokens));
	if (!str)
		return (MSH_SYNTAX_ERROR);
	words = NULL;
	if (expand(&owords, &str, msh) != MSH_SUCCESS)
		return (list_clear(&words, free), free(str), MSH_MEMFAIL);
	if (words->next)
		return (list_clear(&words, free), MSH_SYNTAX_ERROR);
	free(cmd->io.out.name);
	*name = words->content;
	free(word);
	return (MSH_SUCCESS);
}

char	*token_to_str(t_list *token)
{
	char	*str;

	if (!(token && token->content))
		return (NULL);
	str = ((t_token *)token->content)->str;
	free(token->content);
	free(token);
	return (str);
}
