#include "libft.h"
#include "msh.h"
#include "msh_execute.h"
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

void	print_env(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		++i;
	}
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

	cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
    env_free(&msh.env);
}

void	assert_cd_output_error(t_cmd *cmd, char *expected,
		void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
    env_free(&msh.env);
}

void	assert_cd_dir(t_cmd *cmd, char *expected, void (*env_init)(t_msh *))
{
	t_msh	msh;
	char	*buf;

	buf = NULL;
	cmd->io[1] = 1;
    cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	fflush(stdout);
	fflush(stderr);
    buf = getcwd(buf, 0);
	cr_assert_eq(strcmp(buf, expected), 0);
	free(buf);
    env_free(&msh.env);
}

void	assert_cd_status(t_cmd *cmd, int expected, void (*env_init)(t_msh *))
{
	t_msh	msh;
	int		status;

	cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	status = msh_cd(cmd, &msh);
	fflush(stdout);
	cr_assert_eq(status, expected);
    env_free(&msh.env);
}

void	assert_cd_env(t_cmd *cmd, const char *name, int exists, void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	fflush(stdout);
	if (exists)
		cr_assert_not_null(env_search(&msh.env, name));
	else
		cr_assert_null(env_search(&msh.env, name));
	env_free(&msh.env);
}

void	env_with_home(t_msh *msh)
{
	char	*env_sub[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};
    env_init(&msh->env, env_sub);
}

void	env_without_home(t_msh *msh)
{
	char	*env_sub[] = {"LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};
    env_init(&msh->env, env_sub);
}

void	env_without_oldpwd(t_msh *msh)
{
	char	*env_sub[] = {"LOGNAME=jvan-hal", "HOME=/Users/jvan-hal", NULL};
    env_init(&msh->env, env_sub);
}

TestSuite(cd, .init = redirect_stdout);

TestSuite(cd_err, .init = redirect_stderr);

// Test(cd, no_arg_with_home_0)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", NULL};

// 	cmd.argc = 1;
// 	cmd.argv.array = input;
// 	system("cd");
// 	system("mkdir /Users/jvan-hal");
// 	system("mkdir /tmp/cd-no_arg_with_home");
// 	system("cd /tmp/cd-no_arg_with_home");
// 	assert_cd_dir(&cmd, "/Users/jvan-hal", &env_with_home);
// 	system("rmdir /tmp/cd-no_arg_with_home");
// }

// Test(cd, no_arg_with_home_1)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", NULL};

// 	cmd.argc = 1;
// 	cmd.argv.array = input;
// 	system("cd");
// 	system("mkdir /Users/jvan-hal");
// 	assert_cd_status(&cmd, 0, &env_with_home);
// }

Test(cd, no_arg_with_home_2)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("cd");
	system("mkdir /Users/jvan-hal");
	assert_cd_env(&cmd, "OLDPWD", 1, &env_with_home);
}

Test(cd, no_arg_with_home_3)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	system("cd");
	system("mkdir /Users/jvan-hal");
	assert_cd_env(&cmd, "PWD", 0, &env_with_home);
}

Test(cd_err, no_arg_without_home_0)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};
	
	cmd.argc = 1;
	cmd.argv.array = input;
	assert_cd_output_error(&cmd, "msh: cd: HOME not set\n", &env_without_home);
}

Test(cd_err, no_arg_without_home_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	assert_cd_status(&cmd, 1, &env_without_home);
}

Test(cd_err, no_arg_without_home_2)
{
	t_cmd	cmd;
	char	*input[] = {"cd", NULL};

	cmd.argc = 1;
	cmd.argv.array = input;
	assert_cd_env(&cmd, "PWD", 0, &env_without_home);
}

// Test(cd, dash_arg_with_oldpwd_0)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", "-", NULL};

// 	cmd.argc = 2;
// 	cmd.argv.array = input;
// 	system("mkdir /tmp");
// 	system("mkdir /tmp/cd-no_arg_with_home");
// 	system("mkdir /tmp/cd-dash");
// 	system("cd /tmp/cd-no_arg_with_home");
// 	assert_cd_dir(&cmd, "/private/tmp/cd-dash", &env_with_home); //
// 	// system("rmdir /tmp/cd-no_arg_with_home");
// 	// system("rmdir /tmp/cd-dash");
// }

Test(cd, dash_arg_with_oldpwd_1)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_output(&cmd, "/tmp/cd-dash\n", &env_with_home);
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

Test(cd, dash_arg_with_oldpwd_3)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_env(&cmd, "OLDPWD", 1, &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd, dash_arg_with_oldpwd_4)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_env(&cmd, "PWD", 0, &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

// Test(cd, dash_arg_without_oldpwd_0)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", "-", NULL};

// 	cmd.argc = 2;
// 	cmd.argv.array = input;
// 	system("mkdir -p /tmp/cd-no_arg_with_home");
// 	system("mkdir /tmp/cd-dash");
// 	system("cd /tmp/cd-no_arg_with_home");
// 	assert_cd_dir(&cmd, "/private/tmp/cd-dash", &env_without_oldpwd);
// 	system("rmdir /tmp/cd-no_arg_with_home");
// 	system("rmdir /tmp/cd-dash");
// }

// Test(cd_err, dash_arg_without_oldpwd_1)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", "-", NULL};

// 	cmd.argc = 2;
// 	cmd.argv.array = input;
// 	system("mkdir -p /tmp/cd-no_arg_with_home");
// 	system("mkdir /tmp/cd-dash");
// 	system("cd /tmp/cd-no_arg_with_home");
// 	assert_cd_output_error(&cmd, "msh: cd: OLDPWD not set\n", &env_without_oldpwd);
// 	system("rmdir /tmp/cd-no_arg_with_home");
// 	system("rmdir /tmp/cd-dash");
// }

Test(cd_err, dash_arg_without_oldpwd_2)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir -p /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_env(&cmd, "OLDPWD", 0, &env_without_oldpwd);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

Test(cd_err, dash_arg_without_oldpwd_3)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "-", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir -p /tmp/cd-no_arg_with_home");
	system("mkdir /tmp/cd-dash");
	system("cd /tmp/cd-no_arg_with_home");
	assert_cd_env(&cmd, "PWD", 0, &env_without_oldpwd);
	system("rmdir /tmp/cd-no_arg_with_home");
	system("rmdir /tmp/cd-dash");
}

// Test(cd, dir_arg_0)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", "tmp", NULL};

// 	cmd.argc = 2;
// 	cmd.argv.array = input;
// 	system("mkdir /tmp/cd-no_arg_with_home");
// 	assert_cd_dir(&cmd, "/private/tmp", &env_with_home);
// 	system("rmdir /tmp/cd-no_arg_with_home");
// }

// Test(cd, dir_arg_1)
// {
// 	t_cmd	cmd;
// 	char	*input[] = {"cd", "tmp", NULL};

// 	cmd.argc = 2;
// 	cmd.argv.array = input;
// 	system("mkdir /tmp/cd-no_arg_with_home");
// 	assert_cd_status(&cmd, 0, &env_with_home);
// 	system("rmdir /tmp/cd-no_arg_with_home");
// }

Test(cd, dir_arg_2)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "tmp", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	assert_cd_env(&cmd, "OLDPWD", 1, &env_with_home);
	system("rmdir /tmp/cd-no_arg_with_home");
}

Test(cd, dir_arg_3)
{
	t_cmd	cmd;
	char	*input[] = {"cd", "tmp", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	system("mkdir /tmp/cd-no_arg_with_home");
	assert_cd_env(&cmd, "PWD", 0, &env_with_home);
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
	char	*expected = "msh: cd: trmp: No such file or directory\n";

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

Test(cd, inv_dir_arg_3)
{
	t_cmd cmd;
	char *input[] = {"cd", "trmp", NULL};

	cmd.argc = 2;
	cmd.argv.array = input;
	assert_cd_env(&cmd, "PWD", 0, &env_with_home);
}