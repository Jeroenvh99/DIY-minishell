/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 15:41:23 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/23 10:33:30 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"
#include "msh_var.h"

#include "ft_stdio.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>

static void	env_test_interactive(t_env *env);
static void	env_unset_wrapper(t_env *env, char *line);
static void	env_set_wrapper(t_env *env, char *line);
static void	env_view(t_env *env);

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_errno	errno;

	(void) argc;
	(void) argv;
	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (EXIT_FAILURE);
	errno = env_init(env, envp);
	dprintf(2, "env_init: %d\n", errno);
	if (errno != MSH_SUCCESS)
		return (EXIT_FAILURE);
	env_test_interactive(env);
	dprintf(2, "= Packing environment...\n");
	env_pack(env);
	env_view(env);
	env_free(env);
	return (EXIT_SUCCESS);
}

static void	env_test_interactive(t_env *env)
{
	char	*line;
	size_t	len;

	line = ft_getline(1);
	while (line)
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (line[0] == '@')
			env_view(env);
		else if (line[0] == '-')
			env_unset_wrapper(env, line + 1);
		else if (ft_strchr(line, '=') == NULL)
			dprintf(2, "- Value of %s: %s\n", line, env_search(env, line));
		else
			env_set_wrapper(env, line);
		free(line);
		line = ft_getline(1);
	}
}

static void	env_set_wrapper(t_env *env, char *line)
{
	char	*keyval[2];
	t_errno	errno;

	errno = var_parse(&keyval[0], &keyval[1], line);
	if (errno != MSH_SUCCESS)
		return (free(keyval[0]), free(keyval[1]));
	errno = env_set(env, line);
	free(keyval[0]);
	free(keyval[1]);
}

static void	env_unset_wrapper(t_env *env, char *line)
{
	dprintf(2, "- Removing %s from env.\n", line);
	env_unset(env, line);
}

static void	env_view(t_env *env)
{
	size_t	i;

	dprintf(2, "ENVIRONMENT at %p:\n", env);
	if (!env)
		return ;
	dprintf(2, "len = %zu\nused = %zu\nenvp (%p):\n", env->len, env->used, env->envp);
	i = 0;
	while (i < env->len + 1)
	{
		dprintf(2, "> ");
		ft_printf("%s\n", env->envp[i]);
		i++;
	}
}
