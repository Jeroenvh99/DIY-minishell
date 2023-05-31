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

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	assert_exit_output_error(t_cmd *cmd, char *expected)
{
	t_msh	msh;

    cmd->io.err = 2;
	bzero(&msh, sizeof(msh));
	msh_exit(cmd, &msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
}

void	assert_exit_status(t_cmd *cmd, int expected)
{
	t_msh	msh;
	int		status;

    cmd->io.err = 2;
	bzero(&msh, sizeof(msh));
	status = msh_exit(cmd, &msh);
	cr_assert_eq(status, expected);
}

TestSuite(exit, .init=redirect_stderr);

Test(exit, input_empty_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	char	*expected = "";
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_empty_1)
{
	t_cmd cmd;

	char	*input[] = {"exit", NULL};
	cmd.argv.array = input;
	assert_exit_status(&cmd, 0);
}

Test(exit, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", "8", NULL};
	char	*expected = "";
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"exit", "8", NULL};
	cmd.argv.array = input;
	assert_exit_status(&cmd, 8);
}

Test(exit, input_one_2)
{
	t_cmd cmd;

	char	*input[] = {"exit", "d", NULL};
	char	*expected = "exit\nmsh: %s: exit: numeric argument required\n";
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"exit", "d", NULL};
	cmd.argv.array = input;
	assert_exit_status(&cmd, 255);
}

Test(exit, input_two_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", "5", "7", NULL};
	char	*expected = "exit\nmsh: exit: too many arguments\n";
	cmd.argv.array = input;
	assert_exit_output_error(&cmd, expected);
}

Test(exit, input_two_0)
{
	t_cmd cmd;

	char	*input[] = {"exit", "5", "7", NULL};
	cmd.argv.array = input;
	assert_exit_status(&cmd, 1);
}