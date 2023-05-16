/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/16 14:41:08 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../lib/libft/include/ft_string.h"
#include "./../../lib/libft/include/ft_stdio.h"
#include "./../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	env_error(int fd, char *arg)
{
	ft_dprintf(fd, "env: %s: No such file or directory", arg);
}

int	ft_isonlydash(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '-')
		++i;
	return (str[i] == '\0' && i != 2);
}

int	msh_env(int argc, char **argv, t_msh *msh)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argc == 2 && ft_isonlydash(argv[i]))
			return (0);
		if (i == argc - 1 && !(i == 1 && ft_strncmp(argv[i], "--", 3) == 0))
		{
			env_error(2, argv[i]);
			return (127);
		}
		++i;
	}
	print_2d_arr(msh->env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;
	char	**test_args;

	msh = (t_msh *)malloc(sizeof(t_msh));
	msh->env = copy_env(envp);

	test_args = (char **)malloc(sizeof(char *) * 3);
	ft_printf("testing \"env a\"\n");
	test_args[0] = ft_strdup("env");
	test_args[1] = ft_strdup("a");
	test_args[2] = NULL;
	msh_env(2, test_args, msh);
	ft_printf("\n\n");
	ft_printf("testing \"env -\"\n");
	free(test_args[1]);
	test_args[1] = ft_strdup("-");
	msh_env(2, test_args, msh);
	ft_printf("\n\n");
	ft_printf("testing \"env --\"\n");
	free(test_args[1]);
	test_args[1] = ft_strdup("--");
	msh_env(2, test_args, msh);
	ft_printf("\n\n");
}