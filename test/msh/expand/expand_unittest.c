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
#include "msh_expand.h"
#include "msh_env.h"
#include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <stdio.h>

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void assert_expand_str(char *str, char *expected, void (*env_init)(t_msh *))
{
	t_msh msh;

	bzero(&msh, sizeof(msh));
	env_init(&msh);
	expand(NULL, &str, &msh);
	printf("%s", str);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void assert_expand_status(char *str, int expected, void (*env_init)(t_msh *))
{
	t_msh msh;
	int status;

	bzero(&msh, sizeof(msh));
	env_init(&msh);
	status = expand(NULL, &str, &msh);
	cr_assert_eq(status, expected);
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

TestSuite(expand, .init=redirect_stdout);

Test(expand, input_empty_0)
{
	char *in = "";
	char *expected = "";
	assert_expand_str(in, expected, &env_with_home);
}

Test(expand, input_one_0)
{
	char *in = "$HOME";
	char *expected = "/Users/jvan-hal";
	assert_expand_str(in, expected, &env_with_home);
}

Test(expand, input_one_1)
{
	char *in = "$LANG";
	char *expected = "$LANG";
	assert_expand_str(in, expected, &env_with_home);
}
