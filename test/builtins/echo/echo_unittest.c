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

void	assert_echo_output(t_cmd *cmd, char *expected)
{
	t_msh	msh;

    cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
	msh_echo(cmd, &msh);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

TestSuite(echo, .init=redirect_stdout);

Test(echo, input_empty)
{
	t_cmd cmd;

	char	*input[] = {"echo", NULL};
	char	*expected = "\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"echo", "hello", NULL};
	char	*expected = "hello\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"echo", "--", NULL};
	char	*expected = "--\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_one_2)
{
	t_cmd cmd;

	char	*input[] = {"echo", "\n", NULL};
	char	*expected = "\n\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"echo", " ", NULL};
	char	*expected = " \n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_two_0)
{
	t_cmd cmd;

	char	*input[] = {"echo", "hi", "again", NULL};
	char	*expected = "hi again\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_two_1)
{
	t_cmd cmd;

	char	*input[] = {"echo", "hello", "-n", NULL};
	char	*expected = "hello -n\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_five_0)
{
	t_cmd cmd;

	char	*input[] = {"echo", "text", "", "text", "", "hi", NULL};
	char	*expected = "text  text  hi\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_n_opt_0)
{
	t_cmd cmd;

	char	*input[] = {"echo", "-n", NULL};
	char	*expected = "";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_n_opt_1)
{
	t_cmd cmd;

	char	*input[] = {"echo", "-nnnnnnn", NULL};
	char	*expected = "";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_n_opt_2)
{
	t_cmd cmd;

	char	*input[] = {"echo", "-n", "-n", "-n", "-n", NULL};
	char	*expected = "";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_n_opt_arg_0)
{
	t_cmd cmd;

	char	*input[] = {"echo", "-n", "hello", NULL};
	char	*expected = "hello";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_inv_opt_0)
{
	t_cmd cmd;

	char	*input[] = {"echo", "-f", NULL};
	char	*expected = "-f\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}

Test(echo, input_inv_opt_1)
{
	t_cmd cmd;

	char	*input[] = {"echo", "-ng", NULL};
	char	*expected = "-ng\n";
	cmd.argv.array = input;
	assert_echo_output(&cmd, expected);
}