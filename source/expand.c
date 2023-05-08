/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 12:23:49 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/08 18:19:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh_error.h"
#include "msh_var.h"
#include "msh_utils.h"

#include "ft_ctype.h"
#include "ft_hash.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

static char		*find_next_word(char **str, size_t *offset, size_t *var_len, t_hashtable *vars);
static t_errno	expand_substitute(char **str, size_t i, char const *exp, size_t exp_len);
static t_errno	expand_var(char **str, size_t *var_len, t_hashtable *vars);

t_errno	expand(t_list **words, t_hashtable *vars)
{
	char	*str;
	char	*word;
	size_t	offset;
	size_t	var_len;

	str = (*words)->content;
	list_clear(words, NULL);
	offset = 0;
	var_len = 0;
	while (str[offset])
	{
		word = find_next_word(&str, &offset, &var_len, vars);
		if (word == NULL)
			return (free(str), MSH_MEMFAIL);
		if (list_append_ptr(words, word) != MSH_SUCCESS)
			return (free(str), MSH_MEMFAIL);
	}
	free(str);
	return (MSH_SUCCESS);	
}

static char	*find_next_word(char **str, size_t *offset, size_t *var_len, t_hashtable *vars)
{
	char	*word;
	size_t	len;

	(void) offset;
	len = 0;
	while (*str[len])
	{
		if (**str == CHR_VAR && expand_var(str, len, var_len, vars) != MSH_SUCCESS)
			return (NULL);
		len++;
	}
	return (ft_strdup(*str));
}

static t_errno	expand_substitute(char **str, size_t i,
					char const *exp, size_t exp_len)
{
	char		*nstr;
	size_t const nstr_size = ft_strlen(*str) + ft_strlen(exp) - (name_len + 1) + 1;

	nstr = malloc(nstr_size * sizeof(char));
	if (nstr == NULL)
		return (NULL);
	ft_memcpy(nstr, *str, i);
	nstr[i] = '\0';
	ft_strlcat(nstr, exp, nstr_size);
	ft_strlcat(nstr, &(*str)[i + name_len], nstr_size);
	free(*str);
	*str = nstr;
	return (MSH_SUCCESS);
}

static t_errno expand_var(char **str, size_t i, size_t *value_len, t_hashtable *vars)
{
	char	*key;
	size_t	key_len;
	char	*value;

	//als **str == '?': uitgaande waarde
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
