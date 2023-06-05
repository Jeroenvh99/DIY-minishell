#include "libft.h"
#include "msh.h"
#include <criterion/abort.h>
#include <criterion/alloc.h>
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/event.h>
#include <criterion/internal/assert.h>
#include <criterion/new/assert.h>
#include <criterion/new/memory.h>
#include <criterion/new/stream.h>
#include <criterion/options.h>
#include <criterion/output.h>
#include <criterion/parameterized.h>
#include <criterion/redirect.h>
#include <criterion/stats.h>
#include <criterion/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void	env_free_(t_env *env)
{
    while (env->used--)
        free(env->envp[env->used]);
    free(env->envp);
    free(env);
}

t_errno	env_init_(t_env *env, int len, ...)
{
    va_list ap;
    char *s;

    env->envp = (char **)malloc(sizeof(char *) * (len + 1));
    if (env->envp == NULL)
        return (MSH_MEMFAIL);
    env->used = 0;
    va_start(ap, len);
    while (len > 0)
    {
        s = va_arg(ap, char *);
        env->envp[env->used] = ft_strdup(s);
        if (env->envp[env->used] == NULL)
            return (env_free(env), MSH_MEMFAIL);
        env->used++;
        len--;
    }
    va_end(ap);
    env->envp[env->used] = NULL;
}

void	redirect_stdout(void)
{
	cr_redirect_stdout();
}

void	redirect_stderr(void)
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
    env_free_(msh.env);
}

void	assert_cd_output_error(t_cmd *cmd, char *expected,
		void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io.err = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
    env_free_(msh.env);
}

void	assert_cd_dir(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
	t_msh	msh;
	char	*buf;

	buf = NULL;
	cmd->io.out = 1;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	cr_assert_eq(getcwd(buf, 0), expected);
	free(buf);
    env_free_(msh.env);
}

void	assert_cd_status(t_cmd *cmd, int expected, void (*env_init)(t_msh *))
{
	t_msh	msh;
	int		status;

	cmd->io.out = 1;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	status = msh_cd(cmd, &msh);
	cr_assert_eq(status, expected);
    env_free_(msh.env);
}

void	env_with_home(t_msh *msh)
{
	env_init_(msh->env, 3, "HOME=/Users/jvan-hal", "LOGNAME=jvan-hal",
             "OLDPWD=/tmp/cd-dash");
}

void	env_without_home(t_msh *msh)
{
    env_init_(msh->env, 2, "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash");
}

void	env_without_oldpwd(t_msh *msh)
{
    env_init_(msh->env, 2, "LOGNAME=jvan-hal", "HOME=/Users/jvan-hal");
}

TestSuite(cd, .init = redirect_stdout);

TestSuite(cd_err, .init = redirect_stderr);

Test(cd, no_arg_with_home_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_dir(&cmd, getenv("HOME"), &env_with_home);
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
	assert_cd_status(&cmd, 0, &env_with_home);
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
	assert_cd_dir(&cmd, getenv("HOME"), &env_without_home);
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, dash_arg_with_oldpwd_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_dir(&cmd, "/tmp/cd-dash", &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_oldpwd_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_output(&cmd, "/tmp/cd-dash", &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_oldpwd_2)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_status(&cmd, 0, &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_without_oldpwd_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_dir(&cmd, "/tmp/cd-dash", &env_without_oldpwd);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dir_arg_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "tmp", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	assert_cd_dir(&cmd, "/tmp", &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, dir_arg_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "tmp", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	assert_cd_status(&cmd, 0, &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, inv_dir_arg_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "trmp", NULL};
	char	*buf;

	buf = NULL;
	cmd.argc = 2;
	cmd.argv.array = input;
	assert_cd_dir(&cmd, getcwd(buf, 0), &env_with_home);
	free(buf);
}

Test(cd_err, inv_dir_arg_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "trmp", NULL};
	char	*expected = "msh: cd: trmp: No such file or directory";

	cmd.argc = 2;
	cmd.argv.array = input;
	assert_cd_output_error(&cmd, expected, &env_with_home);
}

Test(cd, inv_dir_arg_2)
{
	t_cmd cmd;
	char *input[] = {"cd", "trmp", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	assert_cd_status(&cmd, 1, &env_with_home);
}