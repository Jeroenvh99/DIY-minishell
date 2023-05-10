/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 17:31:20 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include "./../../lib/libft/include/ft_stdio.h"
#include "./../../include/minishell.h"
#include <stdlib.h>

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		++i;
	return (i);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = env_size(env);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	new_env[i] = NULL;
	--i;
	while (i > 0)
	{
		--i;
		new_env[i] = ft_strdup(env[i]);
	}
	return (new_env);
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
*
char	*get_env_var(char *name, char **env)
{
	int		i;
	char	*varname;

	varname = ft_strjoin(name, "=");
	i = 0;
	while (env[i] && !ft_strnstr(env[i], varname, ft_strlen(varname)))
		++i;
	free(varname);
	if (env[i])
		return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}

int	remove_var(char *name, char **env)
{
	int		i;
	char	*varname;

	varname = ft_strjoin(name, "=");
	i = 0;
	while (env[i] && !ft_strnstr(env[i], varname, ft_strlen(varname)))
		++i;
	free(varname);
	if (env[i])
		free(env[i]);
	return (i);
}
