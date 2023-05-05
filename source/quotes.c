#include "msh_parse.h"

#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

static inline int	compare_quotes(char c, t_quote *lquote);

char	*strunquote(char *str)
{
	t_quote	lquote;
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	lquote = NOQUOTE;
	while (str[i])
	{
		offset += compare_quotes(str[i + offset], &lquote);
		str[i] = str[i + offset];
		if (!str[i])
			break ;
		i++;
	}
	return (str);
}

static inline int	compare_quotes(char c, t_quote *lquote)
{
	t_quote	rquote;

	rquote = is_quote(c);
	if (rquote != NOQUOTE)
	{
		if (*lquote == NOQUOTE)
		{
			*lquote = rquote;
			return (1);
		}
		else if (*lquote == rquote)
		{
			*lquote = NOQUOTE;
			return (1);
		}
	}
	return (0);
}
