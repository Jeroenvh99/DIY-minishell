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

void	assert_cd_output(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
    t_msh	msh;

    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_cd(cmd, &msh);
    fflush(stdout);
    cr_assert_stdout_eq_str(expected);
}

void	assert_cd_dir(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
    t_msh	msh;
    char    *buf;

    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    msh_cd(cmd, &msh);
    cr_assert_eq(getcwd(buf, 0), expected);
    free(buf);
}

void	assert_cd_status(t_cmd *cmd, int expected, void (*env_init)(t_msh *))
{
    t_msh	msh;
    int     status;

    cmd->io.out = 1;
    bzero(&msh, sizeof(msh));
    env_init(&msh);
    status = msh_cd(cmd, &msh);
    cr_assert_eq(status, expected);
}

void    env_with_home(t_msh *msh)
{
    char	*environ[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};
    msh->env.envp = environ;
}

void    env_without_home(t_msh *msh)
{
    char	*environ[] = {"LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};
    msh->env.envp = environ;
}

void    env_without_oldpwd(t_msh *msh)
{
    char	*environ[] = {"LOGNAME=jvan-hal", "HOME=/Users/jvan-hal", NULL};
    msh->env.envp = environ;
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
    assert_cd_dir(cmd, getenv("HOME"), &env_with_home);
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
    assert_cd_status(cmd, 0, &env_with_home);
    system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, no_arg_without_home_0)
{
    t_cmd	cmd;
    char	*input[] = {"cd", NULL};

    cmd.argc = 1;
    cmd.argv.array = input;
    system("mkdir /tmp/cd-no_arg_with_home");
    system("cd /tmp/cd-no_arg_with_home");
    assert_cd_dir(cmd, getenv("HOME"), &env_without_home);
    system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, dash_arg_with_oldpwd_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
    assert_cd_dir(cmd, "/tmp/cd-dash", &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_oldpwd_1)
{
    t_cmd	cmd;
    char	*input[] = {"cd", "-", NULL};

    cmd.argc = 1;
    cmd.argv.array = input;
    system("mkdir /tmp/cd-no_arg_with_home");
    system("mkdir /tmp/cd-dash");
    system("cd /tmp/cd-no_arg_with_home");
    assert_cd_output(cmd, "/tmp/cd-dash", &env_with_home);
    system("rmdir /tmp/cd-no_arg_with_home");
    system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_oldpwd_2)
{
    t_cmd	cmd;
    char	*input[] = {"cd", "-", NULL};

    cmd.argc = 1;
    cmd.argv.array = input;
    system("mkdir /tmp/cd-no_arg_with_home");
    system("mkdir /tmp/cd-dash");
    system("cd /tmp/cd-no_arg_with_home");
    assert_cd_status(cmd, 0, &env_with_home);
    system("rmdir /tmp/cd-no_arg_with_home");
    system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_without_oldpwd_0)
{
    t_cmd	cmd;
    char	*input[] = {"cd", "-", NULL};

    cmd.argc = 1;
    cmd.argv.array = input;
    system("mkdir /tmp/cd-no_arg_with_home");
    system("mkdir /tmp/cd-dash");
    system("cd /tmp/cd-no_arg_with_home");
    assert_cd_dir(cmd, "/tmp/cd-dash", &env_without_oldpwd);
    system("rmdir /tmp/cd-no_arg_with_home");
    system("rmdir /tmp/cd-dash");
}

Test(cd, dir_arg_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "tmp", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
    assert_cd_dir(cmd, "/tmp", &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, dir_arg_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "tmp", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
    assert_cd_status(cmd, 0, &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
}