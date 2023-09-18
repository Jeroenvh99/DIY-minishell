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

static size_t	removecurdir(char *str, size_t i);
static void		removeprevdir(char *str, size_t i, size_t j);
static void		removelastslash(char *str);

void	path_canonicalize(char *str)
{
	size_t	i;

	removelastslash(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (str[i + 1] && str[i + 2] && str[i + 1] == '.'
				&& str[i + 2] == '/')
			{
				removeprevdir(str, i - 2, i + 3);
				i += 3;
			}
			else
			{
				i -= removecurdir(str, i);
			}
		}
		++i;
	}
}

static void	removeprevdir(char *str, size_t i, size_t j)
{
	if (i < 0)
		return ;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		--i;
		if (i == 0)
			return ;
	}
	++i;
	while (str[j])
	{
		str[i] = str[j];
		++i;
		++j;
	}
	str[i] = '\0';
}

static size_t	removecurdir(char *str, size_t i)
{
	size_t  j;

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
	while (i > 0)
	{
		if (str[i - 1] != '/')
			break ;
		--i;
	}
	str[i] = '\0';
}
