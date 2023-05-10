#include "./../../lib/libft/include/ft_string.h"
#include <stdio.h>

char	*get_env_var(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], name, ft_strlen(name)))
		++i;
	if (env[i])
		return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	printf("%s\n", get_env_var("HOME=", envp));
	return 0;
}