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

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	assert_unset_env(t_cmd *cmd, char *expected)
{
	t_msh	msh;
	char	*env_sub[] = {"HOME=/tmp/cd-no_arg_with_home", "SHLVL=2", "LANG=en_US.UTF-8", NULL};

    cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
    env_init(&msh.env, env_sub);
	msh_unset(cmd, &msh);
	print_2d_arr(cmd->io[1], msh.env.envp, msh.env.len);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void	assert_unset_output_error(t_cmd *cmd, char *expected)
{
	t_msh	msh;
	char	*env_sub[] = {"HOME=/tmp/cd-no_arg_with_home", "SHLVL=2", "LANG=en_US.UTF-8", NULL};

    cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
    env_init(&msh.env, env_sub);
	msh_unset(cmd, &msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
}

void	assert_unset_envused(t_cmd *cmd, size_t expected)
{
	t_msh	msh;
	char	*env_sub[] = {"HOME=/tmp/cd-no_arg_with_home", "SHLVL=2", "LANG=en_US.UTF-8", NULL};

	bzero(&msh, sizeof(msh));
    env_init(&msh.env, env_sub);
	msh_unset(cmd, &msh);
	cr_assert_eq(msh.env.used, expected);
}

TestSuite(unset, .init=redirect_stdout);

TestSuite(unset_err, .init=redirect_stderr);

Test(unset, input_empty)
{
	t_cmd cmd;

	char	*input[] = {"unset", NULL};
    cmd.argc = 1;
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 3);
}

Test(unset, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"unset", "HOME", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 2);
}

Test(unset, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"unset", "HOME", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_env(&cmd, "(null)\nSHLVL=2\nLANG=en_US.UTF-8\n");
}

Test(unset, input_one_2)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 3);
}

Test(unset, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_env(&cmd, "HOME=/tmp/cd-no_arg_with_home\nSHLVL=2\nLANG=en_US.UTF-8\n");
}

Test(unset_err, input_one_4)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_output_error(&cmd, "msh: unset: OLDPWD does not exist\n");
}

Test(unset_err, input_two_0)
{
	t_cmd cmd;

	char	*input[] = {"unset", "SHLVL", "non", NULL};
    cmd.argc = 3;
	cmd.argv.array = input;
	assert_unset_output_error(&cmd, "msh: unset: non does not exist\n");
}

Test(unset, input_two_1)
{
	t_cmd cmd;

	char	*input[] = {"unset", "SHLVL", "non", NULL};
    cmd.argc = 3;
	cmd.argv.array = input;
	assert_unset_env(&cmd, "HOME=/tmp/cd-no_arg_with_home\nLANG=en_US.UTF-8\n");
}

Test(unset_err, input_three_0)
{
	t_cmd cmd;

	char	*input[] = {"unset", "SHLVL", "non", "HOME", NULL};
    cmd.argc = 4;
	cmd.argv.array = input;
	assert_unset_output_error(&cmd, "msh: unset: non does not exist\n");
}

Test(unset, input_three_1)
{
	t_cmd cmd;

	char	*input[] = {"unset", "SHLVL", "non", "HOME", NULL};
    cmd.argc = 4;
	cmd.argv.array = input;
	assert_unset_env(&cmd, "LANG=en_US.UTF-8\n");
}
