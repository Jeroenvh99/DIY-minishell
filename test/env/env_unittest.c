#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/new/assert.h>
#include <criterion/new/memory.h>
#include <criterion/new/stream.h>
#include <criterion/alloc.h>
#include <criterion/abort.h>
#include <criterion/event.h>
#include <criterion/options.h>
#include <criterion/output.h>
#include <criterion/parameterized.h>
#include <criterion/stats.h>
#include <criterion/types.h>
#include "msh.h"
#include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <stdlib.h>
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

void	print_2d_arr(int fd, char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_dprintf(fd, "%s\n", arr[i]);
		++i;
	}
}

void	env_output(t_env *env, char *expected)
{
	print_2d_arr(1, env->envp, env->len);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

TestSuite(env, .init=redirect_stdout);

Test(env, test_init)
{
	t_env	testenv;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};

	env_init(&testenv, &environ);
	env_output(testenv, "LOGNAME=jvan-hal");
}
