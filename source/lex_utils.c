/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:13:15 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/21 15:59:07 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

#include "ft_string.h"
#include <stdbool.h>

bool	is_metachr(char c)
{
	return (ft_strchr(METACHARS, c));
}

t_quote	is_quote(char c)
{
	char const 	quotes[N_QUOTES] = {'\0', CHR_SQUOTE, CHR_DQUOTE};
	t_quote		id;

	id = 1;
	while (id < N_QUOTES)
	{
		if (c == quotes[id])
			return (id);
		id++;
	}
	return (NOQUOTE);
}
