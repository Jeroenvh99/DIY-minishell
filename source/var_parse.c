/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_parse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/22 08:45:14 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_var.h"
#include "msh_error.h"

#include "ft_string.h"

static inline size_t	is_varstr(char const *str);

/* Attempts to parse `str` to yield a name and value, which are to be allocated
 * to `name` and `value`. Passing NULL for either of these parameters will
 * cause the function to forego parsing of that particular datum. Returns
 * MSH_NO_VARSTR if `str` is not a varstring, MSH_MEMFAIL on memory allocation
 * failure or MSH_SUCCESS on success.
 */
t_errno	var_parse(char **name, char **value, char const *str)
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
	if (value)
	{
		*value = ft_substr(str, boundary + 1, -1);
		if (*value == NULL)
			return (MSH_MEMFAIL);
	}
	return (MSH_SUCCESS);
}

static inline size_t	is_varstr(char const *str)
{
	size_t	i;

	i = 0;
    if (str[i] == '=' || str[i] == '+')
        return (0);
	while (str[i] != '=')
	{
        if (str[i] == '\0')
            return (0);
		if (str[i] == '-')
            return (0);
        if (str[i] == '+')
        {
            if (str[i + i] == '=')
                break ;
            return (0);
        }
        ++i;
	}
	return (i - 1);
}
