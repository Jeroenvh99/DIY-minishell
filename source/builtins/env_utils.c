/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/09 16:11:19 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include "./../../lib/libft/include/ft_stdio.h"
#include "./../../minishell.h"
#include <stdlib.h>

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		++i;
	new_env = (char *)malloc(sizeof(char *) * (i + 1));
	new_env[i] = NULL;
	--i;
	while (i > 0)
	{
		--i;
		new_env[i] = ft_strdup(env[i]);
	}
	return (new_env);
}

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		++i;
	return (i);
}

void	print_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		++i;
	}
}

int	remove_var(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		++i;
	if (env[i])
		free(env[i]);
	return (i);
}
