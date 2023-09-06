/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 12:29:20 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 12:54:19 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_utils.h"

t_quote	is_quote(char c)
{
	char const	quotes[N_QUOTES] = {'\0', '\'', '\"'};
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
