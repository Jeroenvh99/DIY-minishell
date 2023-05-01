/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:37:12 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

#include "msh_debug.h"

static inline t_errno	cmd_add_arg(t_cmd *cmd, t_token *arg);
static inline t_errno	cmd_add_path(t_cmd *cmd, t_token *pathname);
static char				*get_filename(char *pathname);

t_errno	parse_word(t_list **tokens, t_list **cmds)
{
	//execute expander
	return (parse_qword(tokens, cmds));
}

t_errno	parse_qword(t_list **tokens, t_list **cmds)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = cmd_get_current(*cmds);
	token = token_pop(tokens);
	if (!cmd->path)
	{
		if (cmd_add_path(cmd, token) != MSH_SUCCESS)
			return (token_destroy(&token), MSH_MEMFAIL);
	}
	else if (cmd_add_arg(cmd, token) != MSH_SUCCESS)
		return (token_destroy(&token), MSH_MEMFAIL);
	free(token);
	return (MSH_SUCCESS);
}

static inline t_errno	cmd_add_arg(t_cmd *cmd, t_token *arg)
{
	size_t	argc_new;
	char	**argv_new;

	argc_new = cmd->argc + 1;
	argv_new = malloc((argc_new + 1) * sizeof(char *));
	if (argv_new == NULL)
		return (MSH_MEMFAIL);
	ft_memcpy(argv_new, cmd->argv, cmd->argc * sizeof(char *));
	argv_new[cmd->argc] = arg->str;
	argv_new[argc_new] = NULL;
	cmd->argc = argc_new;
	free(cmd->argv);
	cmd->argv = argv_new;
	return (MSH_SUCCESS);
}

static t_errno	cmd_add_path(t_cmd *cmd, t_token *pathname)
{
	cmd->path = pathname->str;
	cmd->argc = 1;
	cmd->argv = malloc(2 * sizeof(char *));
	if (cmd->argv == NULL)
		return (MSH_MEMFAIL);
	cmd->argv[0] = get_filename(cmd->path);
	if (cmd->argv[0] == NULL)
		return (MSH_MEMFAIL);
	cmd->argv[1] = NULL;
	return (MSH_SUCCESS);
}

static char	*get_filename(char *pathname)
{
	size_t	offset;

	offset = ft_strlen(pathname);
	while (offset && pathname[offset - 1] != '/')
		offset--;
	return (ft_strdup(pathname + offset));
}
