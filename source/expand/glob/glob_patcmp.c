/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globcmp.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 22:56:52 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 11:26:57 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "ft_string.h"
#include <stddef.h>

static int	check_esc(char const **pattern);
static int	match_char(char const **pattern, char const **str);
static int	match_asterisk(char const **pattern, char const **str);
static int	match_qmark(char const **pattern, char const **str);

/**
 * @brief	Compare `str` with globpattern `pattern`.
 * @return	1 if `str` matches `pattern`, 0 if it does not.
 * */
int	glob_patcmp(char const *pattern, char const *str)
{
	if (*str == '.' && *pattern != '.')
		return (0);
	while (*pattern && *pattern != '/')
	{
		if (check_esc(&pattern))
		{
			if (!match_char(&pattern, &str))
				return (0);
		}
		else if (*pattern == '*')
		{
			if (!match_asterisk(&pattern, &str))
				return (0);
		}
		else if (*pattern == '?')
		{
			if (!match_qmark(&pattern, &str))
				return (0);
		}
		else if (!match_char(&pattern, &str))
			return (0);
	}
	return (*pattern == *str);
}

static int	check_esc(char const **pattern)
{
	if (**pattern != '\\')
		return (0);
	(*pattern)++;
	return (1);
}

static int	match_char(char const **pattern, char const **str)
{
	if (**pattern != **str)
		return (0);
	(*pattern)++;
	(*str)++;
	return (1);
}

/* I could do _far_ better than this logic. */
static int	match_asterisk(char const **pattern, char const **str)
{
	int	offset;
	int	qmarks;

	while (**pattern == '*')
		(*pattern)++;
	qmarks = 0;
	while ((*pattern)[qmarks] == '?')
		qmarks++;
	offset = ft_strlen(*str);
	if (qmarks && offset <= qmarks)
		return (0);
	while (offset && (*str)[offset] != (*pattern)[qmarks])
		offset--;
	*str += offset;
	*pattern += qmarks;
	return (**str == **pattern);
}

static int	match_qmark(char const **pattern, char const **str)
{
	if (!**str)
		return (0);
	(*str)++;
	(*pattern)++;
	return (1);
}
