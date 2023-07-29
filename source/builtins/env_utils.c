/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/07/29 18:14:03 by jeroen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_error.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include <stdlib.h>

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		++i;
	return (i);
}

void	print_2d_arr(int fd, char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_dprintf(fd, "%s\n", arr[i]);
		++i;
	}
}
