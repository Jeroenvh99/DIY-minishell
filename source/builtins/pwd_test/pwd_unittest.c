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

TestSuite(pwd, .init=redirect_all_std);

void	assert_pwd_cases(char **in, t_status expected_status)
{
	char		*cwd;
	t_msh	shell;

	bzero(&shell, sizeof(t_minishell));
	cwd = realpath(".", NULL);
	if (!cwd)
		return ;
	cwd = ft_strjoin_free(cwd, "\n");
	msh_pwd(in, &shell);
	fflush(stdout);
	cr_assert_stdout_eq_str(cwd);
	cr_assert_eq(shell.status, expected_status);
	free(cwd);
}

Test(pwd, no_arg)
{
	char	*in[] = {"pwd", NULL};
	assert_pwd_cases(in, E_USAGE);
}