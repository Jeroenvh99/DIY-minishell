#include "msh_parse.h"
#include "msh_error.h"
#include "msh_var.h"

#include "ft_ctype.h"
#include "ft_hash.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static t_errno	expand_var(char **str, size_t *var_len t_hashtable *vars);
static t_errno	append_from_expansion(char const **str, t_quote lquote);
static t_errno	expand_substitute(char **str, char const *appendix);

t_list	*expand(char *str, t_hashtable *vars)
{
	t_list	*tokens;
	size_t	var_len;

	str = ft_strdup(str);
	if (str == NULL)
		return (NULL);
	tokens = NULL;
	var_len = 0;
	while (str[i])
	{
		if (expand_process_quote(*str, &lquote))
		{
			i++;
			continue ;
		}
		if (str[i] == CHR_VAR && lquote != SQUOTE
			&& expand_var(&str, i + 1, &var_len, vars) != MSH_SUCCESS)
			return (free(str), list_clear(&tokens, token_destroy), NULL);
		else
			errno = append_from_expansion(&nstr, &str, lquote);
		if (errno != MSH_SUCCESS)
			return (free(str), NULL);
	}
	return (tokens);
}

static size_t	word_len(char **str, size_t *var_len)
{
	size_t	i;
	size_t	len;
	t_quote	lquote;

	len = 0;
	lquote = NOQUOTE;
	while (str[i])
	{
		len++;
	}
	return (len);


static t_errno	expand_substitute(char **str, size_t i, char const *exp, size_t exp_len)
{
	char		*nstr;
	size_t const nstr_size = ft_strlen(*str) + ft_strlen(exp) - (name_len + 1) + 1;

	nstr = malloc(nstr_size * sizeof(char));
	if (nstr == NULL)
		return (NULL);
	ft_strncpy(nstr, *str, i);
	nstr[i] = '\0';
	ft_strlcat(nstr, exp, nstr_size);
	ft_strlcat(nstr, &(*str)[i + name_len]);
	free(*str);
	*str = nstr;
	return (MSH_SUCCESS);
}

static t_errno expand_var(char **str, size_t i, size_t *value_len, t_hashtable *vars)
{
	char	*key;
	size_t	key_len;
	char	*value;

	key_len = 0;
	while (ft_isalnum((*str)[i + 1 + key_len]) || (*str)[i + 1 + key_len] == '_')
		key_len++;
	key = ft_substr(*str, i + 1, key_len);
	if (key == NULL)
		return (MSH_MEMFAIL);
	value = var_search(key, vars);
	free(key);
	*value_len = ft_strlen(value);
	return (expand_substitute(str, i, value, key_len));
}
