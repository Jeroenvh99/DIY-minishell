/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_parse.c                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:45:12 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/19 12:40:04 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_var.h"
#include "msh_error.h"

#include "ft_ctype.h"
#include "ft_string.h"

static inline int	is_varstr(size_t *i, char const *str);

/**
 * @brief	Determine whether `str` constitutes a variable assigment operation.
 * 			If `name` is not NULL, also extract the variable identifier `name`
 * 			from `str`.
 * @return	A status code:
 * 			VAR_NOVAR		`str` is not a variable assignment operation.
 * 			VAR_APPEND		`str` is a variable appending operation.
 * 			VAR_ASSIGN		`str` is a variable assignment operation.
 * 			VAR_INVID		`str` contains an invalid identifier.
 */
int	var_parse(char **name, char const *str)
{
	size_t		boundary;
	int const	stat = is_varstr(&boundary, str);

	if (stat == VAR_INVID || stat == VAR_NOVAR)
		return (stat);
	if (boundary == 0)
		return (VAR_NOVAR);
	if (name)
		*name = ft_substr(str, 0, boundary);
	return (stat);
}

static inline int	is_varstr(size_t *i, char const *str)
{
	*i = 0;
	if (ft_isdigit(str[0]))
		return (VAR_INVID);
	while (str[*i])
	{
		if (!ft_isalnum(str[*i]) && str[*i] != '_')
		{
			if (str[*i] == '=')
				return (VAR_ASSIGN);
			if (str[*i] == '+')
			{
				if (str[*i + 1] == '=')
					return (VAR_APPEND);
			}
			return (VAR_INVID);
		}
		(*i)++;
	}
	return (VAR_NOVAR);
}
