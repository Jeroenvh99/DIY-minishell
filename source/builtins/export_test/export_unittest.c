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

void	print_env(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		++i;
	}
}

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

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	assert_export_output(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io.out = 1;
    cmd->io.out = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_export(cmd, &msh);
	fflush(stderr);
    cr_assert_stdout_eq_str(expected);
    env_free_(&msh.env);
}

void	assert_export_output_err(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io.out = 1;
    cmd->io.out = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_export(cmd, &msh);
	fflush(stderr);
    cr_assert_stderr_eq_str(expected);
    env_free_(&msh.env);
}

void	assert_export_env(t_cmd *cmd, const char *name, int exists, void (*env_init)(t_msh *))
{
    t_msh	msh;

    cmd->io.out = 1;
    cmd->io.out = 2;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_export(cmd, &msh);
    // print_env(msh.env.envp);
    if (exists)
        cr_assert_not_null(env_search(&msh.env, name));
    else
        cr_assert_null(env_search(&msh.env, name));
    env_free_(&msh.env);
}

void	assert_export_env_val(t_cmd *cmd, const char *name, char *name_val, void (*env_init)(t_msh *))
{
    t_msh	msh;

    cmd->io.out = 1;
    cmd->io.out = 2;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_export(cmd, &msh);
    // print_env(msh.env.envp);
    cr_assert_eq(strcmp(env_search(&msh.env, name), name_val), 0);
    env_free_(&msh.env);
}

void	env_with_home(t_msh *msh)
{
    env_init_(&msh->env, 3, "HOME=/Users/jvan-hal", "LOGNAME=jvan-hal",
              "OLDPWD=/tmp/cd-dash");
}

TestSuite(export, .init=redirect_stdout);

TestSuite(export_err, .init=redirect_stderr);

Test(export, input_empty_0)
{
    t_cmd   cmd;
    char    *input[] = {"export", NULL};

    cmd.argc = 1;
    cmd.argv.array = input;
    assert_export_env(&cmd, "HOME", 1, &env_with_home);
    assert_export_env(&cmd, "OLDPWD", 1, &env_with_home);
    assert_export_env(&cmd, "LOGNAME", 1, &env_with_home);
}

Test(export_err, input_empty_1)
{
    t_cmd   cmd;
    char    *input[] = {"export", NULL};
    char    *expected = "";

    cmd.argc = 1;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export, input_empty_2)
{
    t_cmd   cmd;
    char    *input[] = {"export", NULL};
    char    *expected = "declare -x HOME=\"/Users/jvan-hal\"\ndeclare -x LOGNAME=\"jvan-hal\"\ndeclare -x OLDPWD=\"/tmp/cd-dash\"";

    cmd.argc = 1;
    cmd.argv.array = input;
    assert_export_output(&cmd, expected, &env_with_home);
}

Test(export, input_one_0)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=6", NULL};

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env(&cmd, "n", 1, &env_with_home);
}

Test(export_err, input_one_1)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=6", NULL};
    char    *expected = "";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export, input_one_2)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=6", NULL};
    char    *expected = "";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "n", "n=6", &env_with_home);
}

Test(export, input_one_duplicate_0)
{
    t_cmd   cmd;
    char    *input[] = {"export", "HOME=HERE", NULL};

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "HOME", "HOME=HERE", &env_with_home);
}

Test(export, input_one_duplicate_1)
{
    t_cmd   cmd;
    char    *input[] = {"export", "HOME=HERE", NULL};
    char    *expected = "";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_err(&cmd, expected, &env_with_home);
}
