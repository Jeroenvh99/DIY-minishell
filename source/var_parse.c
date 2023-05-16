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
	while (str[i])
	{
		if (str[i] == CHR_VAR_ASSIGN)
			return (i);
		i++;
	}
	return (0);
}
