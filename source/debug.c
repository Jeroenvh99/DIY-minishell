/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 16:54:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/20 14:40:42 by dbasting      ########   odam.nl         */
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
	char	in[1000];

	read(cmd->io[IO_IN], in, 1000);
	printf("> COMMAND:\n"
		"  - argc: %zu\n"
		"  - argv:", cmd->argc);
	i = 0;
	while (i < cmd->argc)
		printf(" <%s>", cmd->argv.array[i++]);
	printf("\n  - input (%d): %s\n"
		"  - output (%d)\n"
		"  - error (%d)\n",
		cmd->io[IO_IN], in, cmd->io[IO_OUT], cmd->io[IO_ERR]);
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
