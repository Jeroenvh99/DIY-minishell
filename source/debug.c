/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 16:54:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 17:50:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_debug.h"
#include "msh.h"
#include "msh_parse.h"
#include "msh_error.h"

#include <stdio.h>

void	token_view(t_token *token)
{
	printf("TOKEN: (%d) %s\n", token->type, token->str);
}

void	cmd_view(t_cmd *cmd)
{
	size_t	i;

	printf("COMMAND:\n"
		"- argc: %zu\n"
		"- argv:", cmd->argc);
	i = 0;
	while (i < cmd->argc)
		printf(" <%s>", cmd->argv[i++]);
	printf("\n- input: %s (mode %d)\n"
		"- output: %s (mode %d)\n"
		"- error: %s (mode %d)\n",
		cmd->io.in.name, cmd->io.in_mode,
		cmd->io.out.name, cmd->io.out_mode,
		cmd->io.err.name, cmd->io.err_mode);
}
