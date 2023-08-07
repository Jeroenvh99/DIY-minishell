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

static void	_env_print(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

void	env_output(t_env *env, char *expected)
{
	_env_print(env->envp);
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
	env_output(&testenv, "LOGNAME=jvan-hal\nSHLVL=1\n");
}

Test(env, test_init_1)
{
	t_env	testenv;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(testenv.len, 4);
}

Test(env, test_init_2)
{
	t_env	testenv;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(testenv.used, 2);
}

Test(env, test_init_3)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, test_init_4)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(testenv.len, 6);
}

Test(env, test_init_5)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", NULL, "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nSHLVL=1\n");
}

Test(env, test_init_6)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", NULL, "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(testenv.len, 5);
}

Test(env, test_init_7)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "SHLVL=6", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "HOME=/Users/jvan-hal\nSHLVL=7\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\n");
}

Test(env, test_init_8)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, test_init_9)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "SHLVL=5", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	env_output(&testenv, "HOME=/Users/jvan-hal\nSHLVL=6\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\n");
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
	cr_assert_null(env_search(&testenv, "HOM"));
}

Test(env, test_search_2)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_null(env_search(&testenv, "SHELL"));
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
	cr_assert_eq(env_entry_get(&testenv, "LOG"), 6);
}

Test(env, entry_get_2)
{
	t_env	testenv;
	char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

	env_init(&testenv, environ);
	cr_assert_eq(env_entry_get(&testenv, "LANG"), 6);
}

Test(env, entry_getval_0)
{
	cr_assert_eq(strcmp(env_entry_getval("LOGNAME=jvan-hal", "LOGNAME"), "jvan-hal"), 0);
}

Test(env, entry_getval_1)
{
	cr_assert_null(env_entry_getval("LOGNAME=jvan-hal", "_"));
}

Test(env, entry_getval_2)
{
	cr_assert_null(env_entry_getval("LOGNAME=jvan-hal", "LOG"));
}

Test(env, entry_getval_3)
{
	cr_assert_null(env_entry_getval("LOGNAME=jvan-hal", ""));
}

Test(env, unset_len_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    cr_assert_eq(testenv.len, 6);
}

Test(env, unset_len_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    cr_assert_eq(testenv.used, 3);
}

Test(env, unset_len_2)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "");
    cr_assert_eq(testenv.len, 6);
}

Test(env, unset_len_3)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "");
    cr_assert_eq(testenv.used, 4);
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

Test(env, unset_output_2)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGN");
    env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, unset_output_3)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "");
    env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, set_output_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set(&testenv, "LANG", "1.6");
    env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\nLANG=1.6\n");
}

Test(env, set_len_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set(&testenv, "LANG", "1.6");
    cr_assert_eq(testenv.len, 6);
}

Test(env, set_len_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set(&testenv, "LANG", "1.6");
    cr_assert_eq(testenv.used, 5);
}

Test(env, set_output_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set(&testenv, "HOME", "hier");
    env_output(&testenv, "HOME=hier\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, set_len_2)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set(&testenv, "HOME", "hier");
    cr_assert_eq(testenv.len, 6);
}

Test(env, set_len_3)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set(&testenv, "HOME", "hier");
    cr_assert_eq(testenv.used, 4);
}

Test(env, set_output_2)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set_entry(&testenv, "SHLVL+=1");
    env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=11\n");
}

Test(env, set_output_3)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set_entry(&testenv, "HOME+=hier");
    env_output(&testenv, "HOME=/Users/jvan-halhier\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, set_len_4)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set_entry(&testenv, "HOME+=hier");
    cr_assert_eq(testenv.len, 6);
}

Test(env, set_len_5)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_set_entry(&testenv, "HOME+=hier");
    cr_assert_eq(testenv.used, 4);
}

Test(env, update_output_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_update(&testenv, "LOGNAME", "1");
    env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=1\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, update_status_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    cr_assert_eq(env_update(&testenv, "LOGNAME", "1"), 0);
}

Test(env, update_len_0)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_update(&testenv, "LOGNAME", "1");
    cr_assert_eq(testenv.len, 6);
}

Test(env, update_len_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_update(&testenv, "LOGNAME", "1");
    cr_assert_eq(testenv.used, 4);
}

Test(env, update_output_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_update(&testenv, "LANG", "4");
    env_output(&testenv, "HOME=/Users/jvan-hal\nLOGNAME=jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}

Test(env, update_status_1)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    cr_assert_eq(env_update(&testenv, "LANG", "4"), 1);
}

Test(env, update_len_2)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_update(&testenv, "LANG", "4");
    cr_assert_eq(testenv.len, 6);
}

Test(env, update_len_3)
{
	t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_update(&testenv, "LANG", "4");
    cr_assert_eq(testenv.used, 4);
}

Test(env, pack_len_0)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    env_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    cr_assert_eq(testenv.len, 6);
}

Test(env, pack_len_1)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    env_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    cr_assert_eq(testenv.used, 2);
}

Test(env, pack_output_0)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "HOME");
    env_unset(&testenv, "OLDPWD");
    env_pack(&testenv);
    env_output(&testenv, "LOGNAME=jvan-hal\nSHLVL=1\n");
}

Test(env, pack_len_2)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_pack(&testenv);
    cr_assert_eq(testenv.len, 6);
}

Test(env, pack_len_3)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_pack(&testenv);
    cr_assert_eq(testenv.used, 3);
}

Test(env, pack_output_1)
{
    t_env   testenv;
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};

    env_init(&testenv, environ);
    env_unset(&testenv, "LOGNAME");
    env_pack(&testenv);
    env_output(&testenv, "HOME=/Users/jvan-hal\nOLDPWD=/tmp/cd-dash\nSHLVL=1\n");
}
