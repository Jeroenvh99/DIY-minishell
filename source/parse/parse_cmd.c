/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:23 by dbasting      #+#    #+#                 */
/*   Updated: 2023/06/20 21:50:42 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

static t_errno			cmd_convert(t_cmd *cmd);
static inline t_errno			cmd_argconvert(t_cmd *cmd);
static inline t_errno			cmd_fdconvert(t_cmd *cmd);

/* Parse `tokens` to create a simple command (i.e. consume tokens until a
 * control character, pipe symbol or the end of the list is reached.
 */
t_errno	parse_cmd(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	t_toktype			type;
	t_argparsef const	argparsefs[N_TOK_ARG] = {
		parse_word,
		parse_input, parse_heredoc,
		parse_output, parse_output_append};
	t_errno				errno;

	while (*tokens && is_argtok((*tokens)->content))
	{
		type = ((t_token *)(*tokens)->content)->type;
		errno = argparsefs[type](cmd, tokens, msh);
		if (errno != MSH_SUCCESS)
			return (cmd_free_list(cmd), errno);
	}
	return (cmd_convert(cmd));
}

/* Convert `cmd` from being linked-list based to be array-based. Also set any
 * undefined file descriptors to the default values.
 */
static t_errno	cmd_convert(t_cmd *cmd)
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