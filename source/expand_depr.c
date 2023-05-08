#include "msh_parse.h"
#include "msh_error.h"
#include "msh_var.h"

#include "ft_ctype.h"
#include "ft_hash.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno	append_from_var(char **nstr, char const **str,
					t_hashtable *vars);
static t_errno	append_from_str(char **nstr, char const **str, t_quote lquote);
static t_errno	expand_strjoin(char **str, char const *appendix);

char	*expand(char const *str, t_hashtable *vars)
{
	char	*nstr;
	t_quote	lquote;
	t_errno	errno;

	if (!str)
		return (NULL);
	nstr = NULL;
	lquote = NOQUOTE;
	while (*str)
	{
		if (expand_process_quote(*str, &lquote))
		{
			str++;
			continue ;
		}
		if (*str == CHR_VAR && lquote != SQUOTE)
			errno = append_from_var(&nstr, &str, vars);
		else
			errno = append_from_str(&nstr, &str, lquote);
		if (errno != MSH_SUCCESS)
			return (free(nstr), NULL);
	}
	return (nstr);
}

static t_errno	append_from_var(char **nstr, char const **str,
					t_hashtable *vars)
{
	char	*name;
	size_t	name_len;
	char	*appendix;

	*str += 1;
	name_len = 0;
	while (ft_isalnum((*str)[name_len]) || (*str)[name_len] == '_')
		name_len++;
	name = ft_substr(*str, 0, name_len);
	if (name == NULL)
		return (MSH_MEMFAIL);
	appendix = var_search(name, vars);
	free(name);
	if (expand_strjoin(nstr, appendix) != MSH_SUCCESS)
		return (MSH_MEMFAIL);
	*str += name_len;
	return (MSH_SUCCESS);
}

static t_errno	append_from_str(char **nstr, char const **str, t_quote lquote)
{
	char	*appendix;
	size_t	len;

	len = 0;
	if (lquote == SQUOTE)
	{
		while ((*str)[len] && !is_closing_quote((*str)[len], lquote))
			len++;
	}
	else
	{
		while ((*str)[len] && !is_closing_quote((*str)[len], lquote)
			&& (*str)[len] != CHR_VAR)
		len++;
	}
	appendix = ft_substr(*str, 0, len);
	if (appendix == NULL)
		return (MSH_MEMFAIL);
	if (expand_strjoin(nstr, appendix) != MSH_SUCCESS)
		return (free(appendix), MSH_MEMFAIL);
	free(appendix);
	*str += len;
	return (MSH_SUCCESS);
}

static t_errno	expand_strjoin(char **str, char const *appendix)
{
	char	*nstr;

	if (!*str)
		nstr = ft_strdup(appendix);
	else
		nstr = ft_strjoin(*str, appendix);
	if (nstr == NULL)
		return (MSH_MEMFAIL);
	free(*str);
	*str = nstr;
	return (MSH_SUCCESS);
}
