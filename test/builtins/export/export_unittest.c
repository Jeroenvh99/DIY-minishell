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
#include "msh_execute.h"
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

	cmd->io[1] = 1;
    cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_export(cmd, &msh);
	fflush(stdout);
    cr_assert_stdout_eq_str(expected);
    env_free(&msh.env);
}

void	assert_export_output_err(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io[1] = 1;
    cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_export(cmd, &msh);
	fflush(stderr);
    cr_assert_stderr_eq_str(expected);
    env_free(&msh.env);
}

void	assert_export_env(t_cmd *cmd, const char *name, int exists, void (*env_init)(t_msh *))
{
    t_msh	msh;

    cmd->io[1] = 1;
    cmd->io[2] = 2;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_export(cmd, &msh);
    if (exists)
        cr_assert_not_null(env_search(&msh.env, name));
    else
        cr_assert_null(env_search(&msh.env, name));
    env_free(&msh.env);
}

void	assert_export_env_val(t_cmd *cmd, const char *name, char *val, void (*env_init)(t_msh *))
{
    t_msh	msh;

    cmd->io[1] = 1;
    cmd->io[2] = 2;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_export(cmd, &msh);
    cr_assert_eq(strcmp(env_search(&msh.env, name), val), 0);
    env_free(&msh.env);
}

void	env_with_home(t_msh *msh)
{
	char	*env_sub[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};
    env_init(&msh->env, env_sub);
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
    char    *expected = "declare -x HOME=\"/Users/jvan-hal\"\ndeclare -x LOGNAME=\"jvan-hal\"\ndeclare -x OLDPWD=\"/tmp/cd-dash\"\ndeclare -x SHLVL=\"1\"\n";

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

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "n", "6", &env_with_home);
}

Test(export, input_one_3)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", NULL};

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env(&cmd, "n", 1, &env_with_home);
}

Test(export_err, input_one_4)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", NULL};
    char    *expected = "";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export, input_one_5)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", NULL};

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "n", "-6", &env_with_home);
}

Test(export_err, input_one_6)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n-=6", NULL};
    char    *expected = "msh: export: `n-=6': not a valid identifier\n";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export_err, input_one_7)
{
    t_cmd   cmd;
    char    *input[] = {"export", "-=6", NULL};
    char    *expected = "msh: export: `-=6': not a valid identifier\n";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export_err, input_one_8)
{
    t_cmd   cmd;
    char    *input[] = {"export", "", NULL};
    char    *expected = "msh: export: `': not a valid identifier\n";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export, input_one_duplicate_0)
{
    t_cmd   cmd;
    char    *input[] = {"export", "HOME=HERE", NULL};

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "HOME", "HERE", &env_with_home);
}

Test(export, input_one_duplicate_1)
{
    t_cmd   cmd;
    char    *input[] = {"export", "HOME=HERE", NULL};
    char    *expected = "";

    cmd.argc = 2;
    cmd.argv.array = input;
    assert_export_output(&cmd, expected, &env_with_home);
}

Test(export_err, input_two_0)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", "-=ip", NULL};
    char    *expected = "msh: export: `-=ip': not a valid identifier\n";

    cmd.argc = 3;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export, input_two_1)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", "-=ip", NULL};

    cmd.argc = 3;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "n", "-6", &env_with_home);
}

Test(export_err, input_three_0)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", "-=ip", "k=e", NULL};
    char    *expected = "msh: export: `-=ip': not a valid identifier\n";

    cmd.argc = 4;
    cmd.argv.array = input;
    assert_export_output_err(&cmd, expected, &env_with_home);
}

Test(export, input_three_1)
{
    t_cmd   cmd;
    char    *input[] = {"export", "n=-6", "-=ip", "k=e", NULL};

    cmd.argc = 4;
    cmd.argv.array = input;
    assert_export_env_val(&cmd, "n", "-6", &env_with_home);
    assert_export_env_val(&cmd, "k", "e", &env_with_home);
}
