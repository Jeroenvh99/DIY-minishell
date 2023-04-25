#include "msh_parse.h"

#include "ft_string.h"
#include <stdbool.h>

bool	is_metachr(char c)
{
	return (ft_strchr(METACHARS, c));
}
