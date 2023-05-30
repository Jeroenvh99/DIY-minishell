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

void	assert_cd_case(t_cmd *cmd, char *expected)
{
    t_msh	msh;
    char	*environ[] = {"LOGNAME=jvan-hal". "OLDPWD=/tmp/cd-dash", NULL};

    bzero(&msh, sizeof(msh));
    msh.env.envp = environ;
    msh_cd(cmd, &msh);
    fflush(stdout);
    cr_assert_stdout_eq_str(expected);
}

void	assert_cd_dir(t_cmd *cmd, char *expected)
{
    t_msh	msh;
    char	*environ[] = {"LOGNAME=jvan-hal". "OLDPWD=/tmp/cd-dash", NULL};

    bzero(&msh, sizeof(msh));
    msh.env.envp = environ;
    msh_cd(cmd, &msh);
    cr_assert_eq(getcwd(buf, 0), expected);
}

TestSuite(cd, .init=redirect_stdout);

TestSuite(cd_err, .init=redirect_stderr);

Test(cd, no_arg_with_home)
{
	t_cmd	cmd;
	char	*buf;
	char	*input[] = {"cd", NULL};

	buf = NULL;
	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("cd /tmp/cd-no_arg_with_home");
	msh_cd(&cmd);
    assert_cd_dir(cmd, getenv("HOME"));
	system("rmdir /tmp/cd-no_arg_with_home");
}