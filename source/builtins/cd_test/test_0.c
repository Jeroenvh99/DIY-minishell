#include "libft.h"
#include "msh.h"
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdarg.h>

void	env_free_(t_env *env)
{
    while (env->used--)
        free(env->envp[env->used]);
    free(env->envp);
}

t_errno	env_init_(t_env *env, int len, ...)
{
    va_list ap;
    char *s;

    env->envp = (char **)malloc(sizeof(char *) * (len + 1));
    if (env->envp == NULL)
        return (MSH_MEMFAIL);
    env->len = len;
    env->used = 0;
    va_start(ap, len);
    while (len > 0)
    {
        s = va_arg(ap, char *);
        env->envp[env->used] = ft_strdup(s);
        if (env->envp[env->used] == NULL)
            return (env_free_(env), MSH_MEMFAIL);
        env->used++;
        len--;
    }
    va_end(ap);
    env->envp[env->used] = NULL;
    return (MSH_SUCCESS);
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

void	assert_cd_dir(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
    t_msh	msh;
    char	*buf;

    buf = NULL;
    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_cd(cmd, &msh);
    buf = getcwd(NULL, 0);
    ft_printf("1 %s\n", buf);
    free(buf);
	print_2d_arr(1, msh.env.envp, 4);
    env_free_(&msh.env);
}

void	env_with_home(t_msh *msh)
{
    env_init_(&msh->env, 3, "HOME=/Users/jvan-hal", "LOGNAME=jvan-hal",
              "OLDPWD=/tmp/cd-dash");
}

int main()
{
    t_cmd	cmd;
    char	*input[] = {"cd", "-", NULL};

    cmd.argc = 2;
    cmd.argv.array = input;
	system("mkdir ./../tmp");
    system("mkdir ./../tmp/cd-no_arg_with_home");
    system("mkdir ./../tmp/cd-dash");
    system("cd ./../tmp/cd-no_arg_with_home");
    assert_cd_dir(&cmd, "/tmp/cd-dash", &env_with_home);
    system("rmdir ./../tmp/cd-no_arg_with_home");
    system("rmdir ./../tmp/cd-dash");
    return 0;
}
