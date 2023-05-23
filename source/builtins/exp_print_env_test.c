#include "./../../lib/libft/include/ft_stdio.h"
#include "./../../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	exp_print_env(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (msh->env[i])
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
	close(1);
}

int main(int argc, char **argv, char **envp)
{
	t_msh *msh;

	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	exp_print_env(msh);
}