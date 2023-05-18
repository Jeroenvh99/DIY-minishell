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

int	is_metachr(char c)
{
	return ((bool)ft_strchr(METACHARS, c) / 1);
}
