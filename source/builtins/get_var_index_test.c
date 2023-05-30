#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	int i;
	t_msh *msh;
	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	msh->envspc = env_size(envp);
	msh->envused = msh->envspc;

	i = get_var_index("HOME", msh->env);
	printf("index: %i, value: %s\n", i, msh->env[i]);
	i = get_var_index("LOG", msh->env);
	printf("index: %i, value: %s\n", i, msh->env[i]);
}