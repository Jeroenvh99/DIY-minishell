/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:07:59 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/01 15:59:29 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_var.h"

#include "ft_ctype.h"

/* Check whether `str` is a valid environment variable identifier. */
int	var_isname(char const *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}
