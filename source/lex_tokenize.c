/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_tokenize.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 14:25:46 by dbasting      #+#    #+#                 */
/*   Updated: 2023/04/18 15:53:44 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

#include "ft_ctype.h"
#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

static char	*token_get(char const **str);
static char	*token_get_qstr(char const **str, char quote);
static char	*token_get_str(char const **str);

char	*lex_tokenize(char const **str)
{
	while (*str)
	{
		if (ft_isspace(**str))
			(*str)++;
		else
			return (token_get(str));
	}
	return (NULL);
}

static char	*token_get(char const **str)
{
	if (**str == CHR_SQUOTE || **str == CHR_DQUOTE)
		return (token_get_qstr(str, **str));
	return (token_get_str(str));
}

static char	*token_get_qstr(char const **str, char quote)
{
	char	*token;
	size_t	len;
	
	len = 1;
	while ((*str)[len] != quote)
		len++;
	token = malloc((len + 1) * sizeof(char));
	if (token == NULL)
		return (NULL);
	(*str)++;
	ft_strlcat(token, *str, len + 1);
	*str += len;
	printf("%p %s\n", token, token);
	return (token);
}

static char	*token_get_str(char const **str)
{
	char	*token;
	size_t	len;

	len = 0;
	while (!ft_isspace(**str))
		len++;
	token = malloc((len + 1) * sizeof(char));
	if (token == NULL)
		return (NULL);
	ft_strlcat(token, *str, len + 1);
	*str += len;
	printf("%p %s\n", token, token);
	return (token);
}
