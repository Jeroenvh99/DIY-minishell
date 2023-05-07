/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/01 16:43:49 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_parse.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "ft_stdlib.h"
#include <stdio.h>

#include <stdlib.h>
#include "msh_debug.h"

static void	cmd_free_wrapper(void *cmd);
//static t_errno	_expand(t_list *tokens);

int	main(void)
{
	t_list	*tokens;
	t_cmd	*cmd;
	t_list	*cmds;
	t_list	*ptr;
	t_errno	errno;

	tokens = NULL;
	cmds = NULL;
	errno = MSH_SUCCESS;
	while (errno == MSH_SUCCESS)
	{
		errno = input_get(&tokens, PROMPT);
		//errno = _expand(tokens);
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (cmd == NULL || list_append_ptr(&cmds, cmd) != MSH_SUCCESS)
			return (1);
		errno = parse(&tokens, &cmds);
		printf("Parser done! (exit: %d)\n", errno);
		ptr = cmds;
		while (ptr)
		{
			cmd_view(ptr->content);
			ptr = ptr->next;
		}
		list_clear(&cmds, cmd_free_wrapper);
	}
	system("leaks minishell");
	return (0);
}

/*static t_errno	_expand(t_list *tokens)
{
	char	*nstr;

	while (tokens)
	{
		nstr = expand(((t_token *)tokens->content)->str, NULL);
		free(((t_token *)tokens->content)->str);
		((t_token *)tokens->content)->str = nstr;
		tokens = tokens->next;
	}
	return (MSH_SUCCESS);
}*/

static void	cmd_free_wrapper(void *cmd)
{
	cmd_delete(cmd);
}
