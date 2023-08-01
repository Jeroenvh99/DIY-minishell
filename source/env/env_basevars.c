/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_basevars.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 19:53:34 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/01 23:56:14 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_error.h"

#include "ft_stdio.h"
#include "ft_stdlib.h"
#include <stdlib.h>

static t_errno	set_shlvl(t_env *env);

t_errno	env_basevars_set(t_env *env)
{
	if (env_update(env, "SHELL", "minishell") == 2)
		return (msh_perror(0), MSH_MEMFAIL);
	return (set_shlvl(env));
}

static t_errno	set_shlvl(t_env *env)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = env_search(env, "SHLVL");
	if (!shlvl_str)
		return (env_set_entry(env, "SHLVL=0"));
	shlvl = ft_atoi(shlvl_str) + 1;
	if (shlvl >= 1000)
	{
		ft_dprintf(2, "msh: warning: shell level (%d) too high; "
			"resetting to 1\n", shlvl);
		shlvl = 1;
	}
	shlvl_str = ft_itoa(shlvl);
	if (env_set(env, "SHLVL", shlvl_str) != MSH_SUCCESS)
		return (free(shlvl_str), MSH_MEMFAIL);
	return (free(shlvl_str), MSH_SUCCESS);
}
