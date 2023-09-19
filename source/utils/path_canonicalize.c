/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-hal <jvan-hal@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:49:16 by dbasting          #+#    #+#             */
/*   Updated: 2023/09/18 14:49:00 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_utils.h"

#include "ft_string.h"
#include <stddef.h>

static void		removecurdir(char *str, size_t i);
static void		removeprevdir(char *str, size_t i);
static size_t	lookforprevdir(char *str, size_t i);
static void		removelastslash(char *str);
static void		removeduplicateslash(char *str);

void	path_canonicalize(char *str)
{
	size_t	i;

	removeduplicateslash(str);
	if (str[1] != '\0')
		removelastslash(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (str[i + 1] && str[i + 1] == '.')
				i += removeprevdir(str, i - 2);
			else
				i -= removecurdir(str, i);
		}
		++i;
	}
	if (str[1] != '\0')
		removelastslash(str);
}

static size_t	removeprevdir(char *str, size_t i)
{
	size_t	j;
	size_t	dotlen;

	dotlen = 2;
	if (i < 0)
		return (0);
	if (str[i + 5] && str[i + 5] == '/')
		dotlen = 3;
	j = i + 2 + dotlen;
	i = lookforprevdir(str, i);
	while (str[j])
	{
		str[i] = str[j];
		++i;
		++j;
	}
	str[i] = '\0';
	return (dotlen);
}

static size_t	lookforprevdir(char *str, size_t i)
{
	size_t	j;

	j = i;
	while (i > 0)
	{
		if (i == 1)
			return (j + 2);
		if (str[i] == '/')
			break ;
		--i;
	}
	++i;
	return (i);
}

static size_t	removecurdir(char *str, size_t i)
{
	size_t	j;

	j = i + 1;
	while (str[j])
	{
		if (str[j] != '/')
			break ;
		++j;
	}
	while (str[j])
	{
		str[i] = str[j];
		++i;
		++j;
	}
	str[i] = '\0';
	return (j - i);
}

static void	removelastslash(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	--i;
	if (str[i] == '/')
		str[i] = '\0';
}

static void	removeduplicateslash(char *str)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
		{
			k = i;
			j = i + 1;
			while (str[j] && str[j] == '/')
				++j;
			++k;
			while (str[j])
			{
				str[k] = str[j];
				++k;
				++j;
			}
			str[k] = '\0';
		}
		++i;
	}
}
