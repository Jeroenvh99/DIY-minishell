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
#include "msh_expand.h"
#include "msh_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static char	*token_to_str(t_list *token);

t_errno	parse_word(t_list **cmds, t_list **tokens, t_msh *msh)
{
	t_cmd *const	cmd = cmd_get_current(*cmds);
	char			*str;

	str = token_to_str(list_pop(tokens));
	if (expand(&cmd->argv.list, &str, msh) != MSH_SUCCESS)
		return (list_clear(&cmd->argv.list, free), free(str), MSH_MEMFAIL);
	return (MSH_SUCCESS);
}

static char	*token_to_str(t_list *token)
{
	char	*str;

	str = ((t_token *)token->content)->str;
	free(token->content);
	free(token);
	return (str);
}
