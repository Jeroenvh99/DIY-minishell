/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdlib.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static size_t	get_argc(t_list *node);
static char		**get_argv(t_list **token_list, size_t argc);
static char		*get_filename(t_list **token_list);

t_errno	parse_cmd(t_list **token_list, t_cmdtable *cmdtable)
{
	t_cmd	*cmd;
	char	*path;
	size_t	argc;
	char	**argv;

	path = ((t_token *)(*token_list)->content)->str;
	argc = get_argc(*token_list);
	argv = get_argv(token_list, cmd->argc);
	if (argv == NULL)
		return (MSH_MEMFAIL);
	cmd = cmd_init(path, argc, argv);
	if (cmd == NULL)
		return (free(path), free_ptr_array((void **)argv, argc + 1),
				MSH_MEMFAIL);
	if (list_append_ptr(cmdtable->cmds, cmd) != MSH_SUCCESS)
		return (cmd_destroy(&cmd), MSH_MEMFAIL);
	return (MSH_SUCCESS);
}

static size_t	get_argc(t_list *node)
{
	size_t	len;

	len = 0;
	while (node)
	{
		if (((t_token *)node->content)->type >= TOK_META_MIN)
			break ;
		len++;
		node = node->next;
	}
	return (len);
}

static char	**get_argv(t_list **token_list, size_t argc)
{
	char	**argv;
	t_list	*node;
	size_t	i;

	argv = ft_calloc(argc + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	argv[0] = get_filename(token_list);
	if (argv[0] == NULL)
		return (free(argv), NULL);
	i = 1;
	while (i < argc)
	{
		node = *token_list;
		argv[i] = ((t_token *)node->content)->str;
		*token_list = node->next;
		list_delete(node, free);
		i++;
	}
	return (argv);
}

static char	*get_filename(t_list **token_list)
{
	char	*filename;
	size_t	offset;
	t_list	*node;

	node = *token_list;
	filename = ((t_token *)node->content)->str;
	offset = ft_strlen(filename);
	while (offset && filename[offset - 1] != CHR_DIRSEP)
		offset--;
	filename = ft_strdup(filename + offset);
	if (filename == NULL)
		return (NULL);
	free(((t_token *)node->content)->str);
	*token_list = node->next;
	list_delete(node, free);
	return (filename);
}
