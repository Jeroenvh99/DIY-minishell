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
#include <unistd.h>

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	assert_cd_output(t_cmd *cmd, char *expected)
{
    t_msh	msh;
    char	*environ[] = {"LOGNAME=jvan-hal". "OLDPWD=/tmp/cd-dash", NULL};

    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    msh.env.envp = environ;
    msh_cd(cmd, &msh);
    fflush(stdout);
    cr_assert_stdout_eq_str(expected);
}

void	assert_cd_dir(t_cmd *cmd, char *expected)
{
    t_msh	msh;
    char    *buf;
    char	*environ[] = {"LOGNAME=jvan-hal". "OLDPWD=/tmp/cd-dash", NULL};

    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    msh.env.envp = environ;
    msh_cd(cmd, &msh);
    cr_assert_eq(getcwd(buf, 0), expected);
    free(buf);
}

void	assert_cd_status(t_cmd *cmd, int expected)
{
    t_msh	msh;
    int     status;
    char	*environ[] = {"LOGNAME=jvan-hal". "OLDPWD=/tmp/cd-dash", NULL};

    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    msh.env.envp = environ;
    status = msh_cd(cmd, &msh);
    cr_assert_eq(status, expected);
}

TestSuite(cd, .init=redirect_stdout);

TestSuite(cd_err, .init=redirect_stderr);

Test(cd, no_arg_with_home_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("cd /tmp/cd-no_arg_with_home");
    assert_cd_dir(cmd, getenv("HOME"));
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, no_arg_with_home_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("cd /tmp/cd-no_arg_with_home");
    assert_cd_status(cmd, 0);
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, dash_arg_with_home_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
    assert_cd_dir(cmd, "/tmp/cd-dash");
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_home_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
    assert_cd_output(cmd, "/tmp/cd-dash");
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_home_2)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
    assert_cd_status(cmd, 0);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}