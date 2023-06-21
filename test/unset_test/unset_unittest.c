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

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void	assert_unset_output(t_cmd *cmd, char *expected)
{
	t_msh	msh;
	char	*environ[] = {"HOME=/tmp/cd-no_arg_with_home", "SHLVL=2", "LANG=en_US.UTF-8", NULL};

    cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
	msh.env.envp = environ;
	msh.env.len = 3;
	msh_unset(cmd, &msh);
	print_2d_arr(msh.env.envp);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void	assert_unset_envused(t_cmd *cmd, int expected)
{
	t_msh	msh;
	char	*environ[] = {"HOME=/tmp/cd-no_arg_with_home", "SHLVL=2", "LANG=en_US.UTF-8", NULL};

	bzero(&msh, sizeof(msh));
	msh.env.envp = environ;
	msh.env.len = 3;
	msh_unset(cmd, &msh);
	cr_assert_eq(msh.env.used, expected);
}

TestSuite(unset, .init=redirect_stdout);

Test(unset, input_empty)
{
	t_cmd cmd;

	char	*input[] = {"unset", NULL};
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 3);
}

Test(unset, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"unset", "HOME", NULL};
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 2);
}

Test(unset, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"unset", "HOME", NULL};
	cmd.argv.array = input;
	assert_unset_output(&cmd, "SHLVL=2\nLANG=en_US.UTF-8\n");
}

Test(unset, input_one_2)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 3);
}

Test(unset, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
	cmd.argv.array = input;
	assert_unset_output(&cmd, "HOME=/tmp/cd-no_arg_with_home\nSHLVL=2\nLANG=en_US.UTF-8\n");
}