#include "ft_string.h"
#include "ft_stdio.h"
#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	exp_print_env(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (i < msh->envused)
	{
		write(1, "declare -x ", 11);
		j = 0;
		while (msh->env[i][j])
		{
			if (msh->env[i][j] == '=')
				break ;
			++j;
		}
		write(1, msh->env[i], j + 1);
		ft_printf("\"%s\"\n", msh->env[i] + j + 1);
		++i;
	}
	// close(1);
}

void	realloc_env(t_msh *msh, int extra_size)
{
	int		i;
	char	**new_env;

	msh->envspc += extra_size;
	i = msh->envspc;
	new_env = (char **)malloc(i * sizeof(char *));
	--i;
	new_env[i] = NULL;
	i -= extra_size;
	while (i > -1)
	{
		new_env[i] = msh->env[i];
		--i;
	}
	free(msh->env);
	msh->env = new_env;
}

int main(int argc, char **argv, char **envp)
{
	t_msh *msh;

	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	msh->envused = env_size(msh->env);
	msh->envspc = msh->envused;

	exp_print_env(msh);
	ft_printf("\n\n");
	ft_printf("size: %i, used: %i\n", msh->envspc, msh->envused);
	realloc_env(msh, 2);
	ft_printf("size: %i, used: %i\n", msh->envspc, msh->envused);
	// msh->env[msh->envused] = ft_strdup("hi=");
	// ++msh->envused;
	// msh->env[msh->envused] = ft_strdup("hi=");
	// ++msh->envused;
	// msh->env[msh->envused] = "hi2=";
	// ++msh->envused;
	// msh->env[msh->envused] = "hi3=";
	// ++msh->envused;
	// exp_print_env(msh);
	print_2d_arr(envp);
	ft_printf("%i\n", env_size(envp));
	return 0;
}