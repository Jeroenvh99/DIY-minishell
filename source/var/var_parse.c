/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/22 14:02:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_var.h"
#include "msh_error.h"

#include "ft_string.h"

static inline size_t	is_varstr(char const *str);

/**
 * @brief	Determine whether `str` constitutes a variable assigment operation.
 * 			If `name` is not NULL, also extract the variable identifier `name`
 * 			from `str`.
 * @return	A status code:
 * 			MSH_SUCCESS		Success.
 * 			MSH_VAR_APPEND	`str` is a variable appending operation.
 * 			MSH_VAR_ASSIGN	`str` is a variable assignment operation.
 * 			MSH_NO_VARSTR	`str` is not a variable assignment operation.
 * 			MSH_MEMFAIL 	A memory allocation error occurred.
 */
t_errno	var_parse(char **name, char const *str)
{
	size_t const	boundary = is_varstr(str);

	if (!boundary)
		return (MSH_NO_VARSTR);
	if (name)
	{
		*name = ft_substr(str, 0, boundary);
		if (*name == NULL)
			return (MSH_MEMFAIL);
	}
	if (str[boundary] == '+')
		return (MSH_VAR_APPEND);
	return (MSH_VAR_ASSIGN);
}

static inline size_t	is_varstr(char const *str)
{
	size_t	i;

	i = 0;
	if (!str[i] || str[i] == '=' || str[i] == '+')
		return (0);
	while (str[i] != '=')
	{
		if (str[i] == '\0')
			return (0);
		if (str[i] == '-')
			return (0);
		if (str[i] == '+')
		{
			if (str[i + 1] && str[i + 1] == '=')
				return (i);
		}
		++i;
	}
	return (i);
}
