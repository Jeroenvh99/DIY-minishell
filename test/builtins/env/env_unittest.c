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
#include <unistd.h>

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	assert_env_output(t_cmd *cmd, char *expected)
{
	t_msh	msh;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};

    cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
	msh.env.envp = environ;
    msh.env.len = 1;
	msh_env(cmd, &msh);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void	assert_env_output_error(t_cmd *cmd, char *expected)
{
	t_msh	msh;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};

	cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
	msh.env.envp = environ;
    msh.env.len = 1;
	msh_env(cmd, &msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
}

void	assert_env_status(t_cmd *cmd, int expected)
{
	t_msh	msh;
	char	*environ[] = {"LOGNAME=jvan-hal", NULL};
	int		status;

    cmd->io[1] = 1;
    cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
	msh.env.envp = environ;
    msh.env.len = 1;
	status = msh_env(cmd, &msh);
	fflush(stdout);
	fflush(stderr);
	cr_assert_eq(status, expected);
}

TestSuite(env, .init=redirect_stdout);

TestSuite(env_err, .init=redirect_stderr);

Test(env, input_empty_0)
{
	t_cmd cmd;

	char	*input[] = {"env", NULL};
	char	*expected = "LOGNAME=jvan-hal\n";
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_env_output(&cmd, expected);
}

Test(env_err, input_empty_1)
{
	t_cmd cmd;

	char	*input[] = {"env", NULL};
	char	*expected = "";
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_env_output_error(&cmd, expected);
}

Test(env, input_empty_2)
{
	t_cmd cmd;

	char	*input[] = {"env", NULL};
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_env_status(&cmd, 0);
}

Test(env, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"env", "-", NULL};
	char	*expected = "";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_env_output(&cmd, expected);
}

Test(env_err, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"env", "-", NULL};
	char	*expected = "msh: env: Invalid argument\n";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_env_output_error(&cmd, expected);
}

Test(env, input_one_2)
{
    t_cmd cmd;

    char	*input[] = {"env", "-", NULL};
    cmd.argc = 2;
    cmd.argv.array = input;
    assert_env_status(&cmd, 127);
}

Test(env, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"env", "--", NULL};
	char	*expected = "";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_env_output(&cmd, expected);
}

Test(env_err, input_one_4)
{
    t_cmd cmd;

    char	*input[] = {"env", "--", NULL};
    char	*expected = "msh: env: Invalid argument\n";
    cmd.argc = 2;
    cmd.argv.array = input;
    assert_env_output_error(&cmd, expected);
}

Test(env, input_one_5)
{
    t_cmd cmd;

    char	*input[] = {"env", "--", NULL};
    cmd.argc = 2;
    cmd.argv.array = input;
    assert_env_status(&cmd, 127);
}
