/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/09 15:57:34 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/26 17:24:29 by jvan-hal      ########   odam.nl         */
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

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = env_size(env);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	new_env[i] = NULL;
	--i;
	while (i >= 0)
	{
		new_env[i] = ft_strdup(env[i]);
		--i;
	}
	return (new_env);
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

int	get_var_index(char *name, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (name[j] && env[i][j] && name[j] != '=' && env[i][j] != '=')
		{
			if ((name[j] == '+' && name[j + 1] == '=')
				|| (name[j] != env[i][j]))
				break ;
			++j;
		}
		if (env[i][j] == '=')
			break ;
		++i;
	}
	if (env[i])
		return (i);
	return (0);
}

t_errno	get_env_var(char *name, char **value, char **env)
{
	int		i;
	char	*varname;

	i = 0;
	varname = ft_strjoin(name, "=");
	if (!varname)
		return (MSH_MEMFAIL);
	while (env[i] && !ft_strnstr(env[i], varname, ft_strlen(varname)))
		++i;
	if (env[i])
		*value = ft_strchr(env[i], '=') + 1;
	else
		return (MSH_NO_VARSTR);
	free(varname);
	return (MSH_SUCCESS);
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
	if (!env[i])
		return (-1);
	free(env[i]);
	return (i);
}
