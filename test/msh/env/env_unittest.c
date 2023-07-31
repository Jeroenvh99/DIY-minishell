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

Test(env, test_search_0)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output_val(&testenv, "HOME", "/Users/jvan-hal");
}

Test(env, test_search_1)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq_null(env_search(&testenv, "SHLVL"));
}

Test(env, entry_get_0)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(env_entry_get(&testenv, "LOGNAME"), 1);
}

Test(env, entry_get_1)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(env_entry_get(&testenv, "LANG"), 3);
}

Test(env, entry_getval_0)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(strcmp(env_entry_getval(&testenv, "LOGNAME"), "jvan-hal"), 0);
}

Test(env, entry_getval_1)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq_null(env_entry_getval(&testenv, "_"));
}

Test(env, unset_len_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    cr_assert_eq(testenv.len, 3);
}

Test(env, unset_len_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    cr_assert_eq(testenv.used, 2);
}

Test(env, unset_output_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    cr_assert_null(env_search(&testenv, "HOME"));
}

Test(env, unset_output_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_output(&testenv, "HOME=/Users/jvan-hal\n");
}

Test(env, pack_len_0)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    env_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    cr_assert_eq(testenv.len, 3);
}

Test(env, pack_len_1)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    env_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    cr_assert_eq(testenv.used, 1);
}

Test(env, pack_output_0)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    env_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    env_output(&testenv, "LOGNAME=jvan-hal\n");
}

Test(env, pack_len_2)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_pack(&testenv);
    cr_assert_eq(testenv.len, 3);
}

Test(env, pack_len_3)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_pack(&testenv);
    cr_assert_eq(testenv.used, 2);
}

Test(env, pack_output_1)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_pack(&testenv);
    env_output(&testenv, "HOME=/Users/jvan-hal\nOLDPWD=/tmp/cd-dash\n");
}
