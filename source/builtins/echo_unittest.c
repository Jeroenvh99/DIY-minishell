# include <criterion/criterion.h>
# include <criterion/redirect.h>
# include <criterion/new/assert.h>
# include <criterion/new/memory.h>
# include <criterion/new/stream.h>
# include <criterion/alloc.h>
# include <criterion/abort.h>
# include <criterion/event.h>
# include <criterion/options.h>
# include <criterion/output.h>
# include <criterion/parameterized.h>
# include <criterion/stats.h>
# include <criterion/types.h>
# include "msh.h"
# include "libft.h"
# include <criterion/assert.h>
# include <criterion/internal/assert.h>

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void	assert_echo_case(t_cmd *cmd, char *expected)
{
	t_msh	msh;

	bzero(&msh, sizeof(msh));
	msh_echo(cmd, &msh);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

TestSuite(echo, .init=redirect_stdout);

Test(echo, input_empty)
{
	t_cmd cmd;

	char		*input[] = {"echo", NULL};
	char		*expected = "\n";
	cmd.argv.array = input;
	cmd.io.out = 1;
	assert_echo_case(&cmd, expected);
}