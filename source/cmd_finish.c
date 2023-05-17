#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

static t_errno	cmd_argconvert(t_cmd *cmd);
static t_errno	cmd_fdconvert(t_cmd *cmd);

t_errno	cmd_finish(t_cmd *cmd)
{
	t_errno	errno;

	errno = cmd_argconvert(cmd);
	if (errno != MSH_SUCCESS)
		return (errno);
	return (cmd_fdconvert(cmd));
}

static t_errno	cmd_argconvert(t_cmd *cmd)
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

static t_errno	cmd_fdconvert(t_cmd *cmd)
{
	if (cmd->io.in == -1)
		cmd->io.in = STDIN_FILENO;
	if (cmd->io.out == -1)
		cmd->io.out = STDOUT_FILENO;
	if (cmd->io.err == -1)
		cmd->io.err = STDERR_FILENO;
	return (MSH_SUCCESS);
}
