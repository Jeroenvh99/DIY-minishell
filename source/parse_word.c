/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 18:14:01 by dbasting      ########   odam.nl         */
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

static inline t_errno	cmd_add_arg(t_cmd *cmd, char *arg);
//static inline t_errno	cmd_add_path(t_cmd *cmd, t_token *pathname);
//static char		*get_filename(char *pathname);
static t_list	*token_to_word(t_list *token);

t_errno	parse_word(t_list **tokens, t_list **cmds/*,t_hashtable *locvars*/)
{
	t_cmd	*cmd;
	t_list	*words;
	char	*word;

	cmd = cmd_get_current(*cmds);
	words = token_to_word(list_pop(tokens));
	if (expand(&words, NULL) != MSH_SUCCESS)
		return (list_clear(&words, free), MSH_MEMFAIL);
	while (words)
	{
		word = list_pop_ptr(&words);
		if (cmd_add_arg(cmd, word) != MSH_SUCCESS)
			return (free(word), MSH_MEMFAIL);
		free(word);
	}
	return (MSH_SUCCESS);
}

static inline t_errno	cmd_add_arg(t_cmd *cmd, char *arg)
{
	size_t	argc_new;
	char	**argv_new;

	argc_new = cmd->argc + 1;
	argv_new = malloc((argc_new + 1) * sizeof(char *));
	if (argv_new == NULL)
		return (MSH_MEMFAIL);
	ft_memcpy(argv_new, cmd->argv, cmd->argc * sizeof(char *));
	argv_new[cmd->argc] = arg;
	argv_new[argc_new] = NULL;
	cmd->argc = argc_new;
	free(cmd->argv);
	cmd->argv = argv_new;
	return (MSH_SUCCESS);
}

/*static t_errno	cmd_add_path(t_cmd *cmd, char *pathname)
{
	cmd->path = pathname;
	cmd->argc = 1;
	cmd->argv = malloc(2 * sizeof(char *));
	if (cmd->argv == NULL)
		return (MSH_MEMFAIL);
	cmd->argv[0] = get_filename(cmd->path);
	if (cmd->argv[0] == NULL)
		return (MSH_MEMFAIL);
	cmd->argv[1] = NULL;
	return (MSH_SUCCESS);
}*/

/*static char	*get_filename(char *pathname)
{
	size_t	offset;

	offset = ft_strlen(pathname);
	while (offset && pathname[offset - 1] != '/')
		offset--;
	return (ft_strdup(pathname + offset));
}*/

t_list	*token_to_word(t_list *token)
{
	char	*str;

	str = ((t_token *)token->content)->str;
	free(token->content);
	token->content = str;
	return (token);
}
	
