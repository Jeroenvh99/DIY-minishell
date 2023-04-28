/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_parse.h"

#include "ft_list.h"
#include <readline/readline.h>
#include <stdlib.h>

t_errno	input_get(t_list **token_list, char const *prompt)
{
	char	*line;
	t_errno	errno;

	line = readline(prompt);
	if (line == NULL)
		return (MSH_MEMFAIL);
		//Maar: NULL hoeft niet louter het gevolg van een falende malloc te zijn!
	errno = lex(token_list, line);
	free(line);
	if (errno == MSH_INCOMPLETE_TOKEN)
		return (input_get(token_list, PROMPT_CONT));
	return (errno);
}
