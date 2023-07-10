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

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	env_free_(t_env *env)
{
    while (env->used--)
        free(env->envp[env->used]);
    free(env->envp);
}

t_errno	env_init_(t_env *env, int len, ...)
{
    va_list ap;
    char *s;

    env->envp = (char **)malloc(sizeof(char *) * (len + 1));
    if (env->envp == NULL)
        return (MSH_MEMFAIL);
    env->len = len;
    env->used = 0;
    va_start(ap, len);
    while (len > 0)
    {
        s = va_arg(ap, char *);
        env->envp[env->used] = ft_strdup(s);
        if (env->envp[env->used] == NULL)
            return (env_free_(env), MSH_MEMFAIL);
        env->used++;
        len--;
    }
    va_end(ap);
    env->envp[env->used] = NULL;
    return (MSH_SUCCESS);
}

void	assert_unset_env(t_cmd *cmd, char *expected)
{
	t_msh	msh;

    cmd->io[1] = 1;
	bzero(&msh, sizeof(msh));
    env_init_(&msh.env, 3, "HOME=/tmp/cd-no_arg_with_home", "SHLVL=2",
              "LANG=en_US.UTF-8");
	msh_unset(cmd, &msh);
	print_2d_arr(cmd->io[1], msh.env.envp, msh.env.len);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void	assert_unset_output_error(t_cmd *cmd, char *expected)
{
	t_msh	msh;

    cmd->io[2] = 2;
	bzero(&msh, sizeof(msh));
    env_init_(&msh.env, 3, "HOME=/tmp/cd-no_arg_with_home", "SHLVL=2",
              "LANG=en_US.UTF-8");
	msh_unset(cmd, &msh);
	fflush(stderr);
	cr_assert_stderr_eq_str(expected);
}

void	assert_unset_envused(t_cmd *cmd, size_t expected)
{
	t_msh	msh;

	bzero(&msh, sizeof(msh));
    env_init_(&msh.env, 3, "HOME=/tmp/cd-no_arg_with_home", "SHLVL=2",
              "LANG=en_US.UTF-8");
	msh_unset(cmd, &msh);
	cr_assert_eq(msh.env.used, expected);
}

TestSuite(unset, .init=redirect_stdout);

TestSuite(unset_err, .init=redirect_stderr);

Test(unset, input_empty)
{
	t_cmd cmd;

	char	*input[] = {"unset", NULL};
    cmd.argc = 1;
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 3);
}

Test(unset, input_one_0)
{
	t_cmd cmd;

	char	*input[] = {"unset", "HOME", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 2);
}

Test(unset, input_one_1)
{
	t_cmd cmd;

	char	*input[] = {"unset", "HOME", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_env(&cmd, "(null)\nSHLVL=2\nLANG=en_US.UTF-8\n");
}

Test(unset, input_one_2)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_envused(&cmd, 3);
}

Test(unset, input_one_3)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_env(&cmd, "HOME=/tmp/cd-no_arg_with_home\nSHLVL=2\nLANG=en_US.UTF-8\n");
}

Test(unset_err, input_one_4)
{
	t_cmd cmd;

	char	*input[] = {"unset", "OLDPWD", NULL};
    cmd.argc = 2;
	cmd.argv.array = input;
	assert_unset_output_error(&cmd, "msh: unset: OLDPWD does not exist\n");
}