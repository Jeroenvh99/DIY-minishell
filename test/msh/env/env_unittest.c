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

void    env_output_val(t_env *env, char *name, char *val)
{
    cr_assert_eq(strcmp(env_search(env, name), val), 0);
}

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

TestSuite(env, .init=redirect_stdout);

Test(env, test_init_0)
{
	t_env	testenv;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "LOGNAME=jvan-hal\n");
}

Test(env, test_init_1)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\n");
}

Test(env, test_init_2)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output_val(&testenv, "HOME", "/Users/jvan-hal");
}

Test(env, pack_len_0)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    msh_unset(&testenv, "HOME");
    msh_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    cr_assert_eq(testenv.len, 3);
}

Test(env, pack_len_1)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    msh_unset(&testenv, "HOME");
    msh_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    cr_assert_eq(testenv.used, 1);
}
