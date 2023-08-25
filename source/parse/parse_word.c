/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 11:59:25 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_expand.h"
#include "list_utils.h"

#include "ft_list.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

/* Parse a word: perform expansion and word splitting and append the results
 * onto `cmd`.
 */
t_errno	parse_word(t_cmd *cmd, t_list **tokens, t_msh *msh)
{
	char	*str;

	str = token_to_str(list_pop_ptr(tokens));
	if (expand(&cmd->argv.list, &str, msh) != MSH_SUCCESS)
		return (list_clear(&cmd->argv.list, free), free(str), MSH_MEMFAIL);
	free(str);
	return (MSH_SUCCESS);
}
