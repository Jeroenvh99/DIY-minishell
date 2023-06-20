/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_finish.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:23 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/20 17:06:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

static inline t_errno	cmd_argconvert(t_cmd *cmd);
static inline t_errno	cmd_fdconvert(t_cmd *cmd);

t_errno	cmd_finish(t_cmd *cmd)
{
	t_errno	errno;
	
	errno = cmd_argconvert(cmd);
	if (errno != MSH_SUCCESS)
		return (errno);
	return (cmd_fdconvert(cmd));
}

static inline t_errno	cmd_argconvert(t_cmd *cmd)
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

static inline t_errno	cmd_fdconvert(t_cmd *cmd)
{
	cmd->io[IO_ERR] = STDERR_FILENO;
	return (MSH_SUCCESS);
}
