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
#include "msh_utils.h"
#include "msh_execute.h"
#include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <stdlib.h>

void	msh_deinit(t_msh *msh)
{
	env_free(&msh->env);
	// list_clear(&msh->cmds, (t_freef)cmd_free);
}

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void	assert_exit_output(t_cmd *cmd, char *expected)
{
	t_msh	*msh;

    cmd->io[1] = 1;
	cmd->io[2] = 2;
	msh = (t_msh *)malloc(sizeof(t_msh));
	bzero(msh, sizeof(t_msh));
	msh_exit(cmd, msh);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void	assert_exit_output_error(t_cmd *cmd, char *expected)
{
	t_msh	*msh;

	cmd->io[1] = 1;
    cmd->io[2] = 2;
    msh = (t_msh *)malloc(sizeof(t_msh));
	bzero(msh, sizeof(t_msh));
	msh_exit(cmd, msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
}

void	assert_exit_status(t_cmd *cmd, int expected)
{
	t_msh	*msh;
	int		status;

    cmd->io[1] = 1;
    cmd->io[2] = 2;
	msh = (t_msh *)malloc(sizeof(t_msh));
	bzero(msh, sizeof(t_msh));
	msh->g_msh->exit = expected;
	status = msh_exit(cmd, msh);
	cr_assert_eq(status, expected);
}

TestSuite(exit, .init=redirect_stdout);

TestSuite(exit_err, .init=redirect_stderr);

Test(exit, input_empty_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	char	*expected = "exit\n";
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_exit_output(&cmd, expected);
}

Test(exit_err, input_empty_1)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	char	*expected = "";
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_empty_2)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_exit_status(&cmd, 0);
}

Test(exit, input_empty_3)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	char	*expected = "exit\n";
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_exit_output(&cmd, expected);
}

Test(exit_err, input_empty_4)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	char	*expected = "";
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_empty_5)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_exit_status(&cmd, 3);
}

Test(exit, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", "8", NULL};
	char	*expected = "exit\n";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_exit_output(&cmd, expected);
}

Test(exit_err, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"exit", "8", NULL};
	char	*expected = "";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_one_2)
{
	t_cmd cmd;

	char	*input[] = {"exit", "8", NULL};
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_exit_status(&cmd, 8);
}

Test(exit, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"exit", "d", NULL};
	char	*expected = "exit\n";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_exit_output(&cmd, expected);
}

Test(exit_err, input_one_4)
{
	t_cmd cmd;

	char	*input[] = {"exit", "d", NULL};
	char	*expected = "msh: exit: d: numeric argument required\n";
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_one_5)
{
	t_cmd cmd;

	char	*input[] = {"exit", "d", NULL};
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_exit_status(&cmd, 255);
}

Test(exit, input_two_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", "5", "7", NULL};
	char	*expected = "";
	cmd.argc = 3;
	cmd.argv.array = input;
	assert_exit_output(&cmd, expected);
}

Test(exit_err, input_two_1)
{
	t_cmd cmd;

	char	*input[] = {"exit", "5", "7", NULL};
	char	*expected = "exit: too many arguments\n";
	cmd.argc = 3;
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_two_2)
{
	t_cmd cmd;

	char	*input[] = {"exit", "5", "7", NULL};
	cmd.argc = 3;
	cmd.argv.array = input;
	assert_exit_status(&cmd, 1);
}
