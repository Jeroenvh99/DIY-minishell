/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:50:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/09 14:16:45 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	msh_unset(int argc, char **argv, t_msh *msh)
{
	int	i;
	int	j;

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (msh->env[j] && ft_strncmp(msh->env[j], argv[i],
				ft_strlen(argv[i])) == 0)
			++j;
		if (msh->env[j])
		{
			free(msh->env[j]);
			while (msh->env[j + 1])
			{
				msh->env[j] = msh->env[j + 1];
				++j
			}
			msh->env[j - 1] = NULL;
		}
		++i;
	}
	--(msh->envused);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_msh *msh;
	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);
	msh_unset(argc, argv, msh);
}