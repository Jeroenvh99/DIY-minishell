/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 11:50:28 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 16:02:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_expand.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

int	is_argtok(t_token const *token)
{
	return (token && token->type < TOK_PIPE);
}

int	is_ctltok(t_token const *token)
{
	return (token && token->type >= TOK_AND && token->type < TOK_INVALID);
}

t_errno	parse_iofile(char **name, t_list **tokens, t_msh *msh)
{
	char *const	str = token_to_str(list_pop_ptr(tokens));
	char		*dup;
	t_list		*words;
	t_errno		errno;

	if (!str)
		return (MSH_SYNTAX_ERROR);
	dup = ft_strdup(str);
	if (!dup)
		return (free(str), MSH_MEMFAIL);
	words = NULL;
	errno = expand(&words, &dup, msh);
	free(dup);
	if (errno != MSH_SUCCESS)
		return (free(str), list_clear(&words, free), MSH_MEMFAIL);
	if (words->next)
	{
		ft_dprintf(2, "msh: %s: Ambiguous redirect.\n", str);
		return (free(str), list_clear(&words, free), MSH_SYNTAX_ERROR);
	}
	*name = list_pop_ptr(&words);
	free(str);
	return (MSH_SUCCESS);
}

char	*token_to_str(t_token *token)
{
	char	*str;

	if (!token)
		return (NULL);
	str = token->str;
	free(token);
	token = NULL;
	return (str);
}
