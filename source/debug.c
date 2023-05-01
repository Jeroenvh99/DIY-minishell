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
			"- path: %s\n"
			"- argc: %zu\n"
			"- argv:", cmd->path, cmd->argc);
	i = 0;
	while (i < cmd->argc)
		printf(" %s", cmd->argv[i++]);
	printf("\n");
	printf("- input: %s (mode %d)\n"
			"- output: %s (mode %d)\n"
			"- error: %s (mode %d)\n",
			cmd->io.in, cmd->io.in_mode,
			cmd->io.out, cmd->io.out_mode,
			cmd->io.err, cmd->io.err_mode);
}
