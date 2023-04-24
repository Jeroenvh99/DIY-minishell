#include "msh.h"
#include "msh_parse.h"
#include "msh_error.h"

#include "ft_list.h"
#include <stdlib.h>

t_cmdtable	*cmdtable_init(t_list *tokens)
{
	t_cmdtable	*cmdtable;
	
	cmdtable = malloc(sizeof(cmdtable));
	if (cmdtable == NULL)
		return (NULL);
	cmdtable->cmds = NULL;
	if (parse(tokens, &cmdtable->cmds, &cmdtable->io) != MSH_SUCCESS)
		return (cmdtable_destroy(&cmdtable), NULL);
	return (cmdtable);
}

void	cmdtable_destroy(**t_cmdtable cmdtable)
{
	list_clear(&(*cmdtable)->cmds, cmd_destroy);
	free(*cmdtable);
	*cmdtable = NULL;
}

void	cmd_destroy(t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while ((*cmd)->opt[i])
		free((*cmd)->opt[i++]);
	free((*cmd)->opts);
	free((*cmd)->name);
	free((*cmd)->path);
	free(*cmd);
	*cmd = NULL;
}
