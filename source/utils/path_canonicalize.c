/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   path_canonicalize.c                                :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jvan-hal <jvan-hal@student.codam.nl>	   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/09/18 13:49:16 by dbasting		  #+#	#+#			 */
/*   Updated: 2023/09/18 15:23:11 by dbasting         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "msh_utils.h"

#include "ft_string.h"
#include <stddef.h>

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
	return (i);
}

size_t	removeprevdir(char *str, size_t i)
{
	size_t	j;

	j = i + 3;
	if (i < 0)
		return (0);
	if (str[i + 4] && str[i + 4] == '/')
		++j;
	i = lookforprevdir(str, i);
	while (str[j])
	{
		str[i] = str[j];
		++i;
		++j;
	}
	str[i] = '\0';
	return (j - i);
}

size_t	removecurdir(char *str, size_t i)
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

void	removelastslash(char *str)
{
	size_t	i;

	i = ft_strlen(str);
	--i;
	if (str[i] == '/')
		str[i] = '\0';
}

void	removeduplicateslash(char *str)
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
