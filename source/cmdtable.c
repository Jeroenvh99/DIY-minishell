#include "msh.h"
#include "msh_parse.h"
#include "msh_error.h"

#include "ft_list.h"
#include <stdlib.h>

void	cmdtable_destroy(t_cmdtable **cmdtable)
{
	list_clear(&(*cmdtable)->cmds, cmd_destroy);
	free(*cmdtable);
	*cmdtable = NULL;
}
