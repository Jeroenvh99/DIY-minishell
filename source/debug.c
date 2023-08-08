/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 16:54:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 14:34:54 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_debug.h"
#include "msh.h"
#include "msh_parse.h"
#include "msh_error.h"

#include "ft_list.h"
#include <stdio.h>
#include <unistd.h>

void	token_view(t_token *token)
{
	printf("TOKEN: (%d) %s\n", token->type, token->str);
}

void	tokens_view(t_list *tokens)
{
	while (tokens)
	{
		token_view(tokens->content);
		tokens = tokens->next;
	}
}

void	cmd_view(t_cmd *cmd)
{
	size_t	i;

	printf("> COMMAND (in subsh %d):\n"
		"  - argc: %zu\n"
		"  - argv:", cmd->subsh, cmd->argc);
	i = 0;
	while (i < cmd->argc)
		printf(" <%s>", cmd->argv.array[i++]);
	printf("\n  - input (%d) [%s]\n"
		"  - output (%d)\n"
		"  - error (%d)\n",
		cmd->io[IO_IN], "", cmd->io[IO_OUT], cmd->io[IO_ERR]);
}

void	cmds_view(t_list *cmds)
{
	printf("PIPELINE:\n");
	while (cmds)
	{
		cmd_view(cmds->content);
		cmds = cmds->next;
	}
	printf("---------\n");
}

void	cmdtree_view(t_cmdtree *tree, int offset)
{
	char const *const	ops[] = {"", "&&", "||", "(", ")"};
	int					i;

	i = 0;
	while (i++ < offset)
		printf("\t");
	if (!tree)
	{
		printf("[...]\n");
		return ;
	}
	if (tree->op)
	{
		printf("BRANCH (%s)\n", ops[tree->op]);
		cmdtree_view(tree->data.branches[TREE_LEFT], offset + 1);
		cmdtree_view(tree->data.branches[TREE_RIGHT], offset + 1);
	}
	else
		printf("PIPELINE (%zu): %s\n",
			list_size(tree->data.pipeline),
			((t_cmd *)(tree->data.pipeline->content))->argv.array[0]);
}
