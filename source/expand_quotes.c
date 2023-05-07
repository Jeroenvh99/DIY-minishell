#include "msh_parse.h"

#include <stddef.h>

int	expand_process_quote(char c, t_quote *lquote)
{
	t_quote const	rquote = is_quote(c);

	if (*lquote == NOQUOTE)
	{
		if (rquote != NOQUOTE)
		{
			*lquote = rquote;
			return (1);
		}
	}
	else if (rquote == *lquote)
	{
		*lquote = NOQUOTE;
		return (1);
	}
	return (0);
}

t_quote	is_quote(char c)
{
	char const	quotes[N_QUOTES] = {'\0', CHR_SQUOTE, CHR_DQUOTE};
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

int	is_closing_quote(char c, t_quote lquote)
{
	if (!lquote)
		return (0);
	if (is_quote(c) == lquote)
		return (1);
	return (0);
}
