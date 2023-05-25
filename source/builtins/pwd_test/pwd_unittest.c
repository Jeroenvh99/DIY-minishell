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

TestSuite(pwd, .init=redirect_stdout);

void	assert_pwd_cases(t_cmd *cmd, t_char *dir)
{
	t_msh	msh;
	char	*expect_dir;

	expect_dir = ft_strjoin(dir, "\n");
	msh_pwd(cmd, &msh);
	fflush(stdout);
	cr_assert_stdout_eq_str(expect_dir);
	free(expect_dir);
}

Test(pwd, no_arg)
{
	char	*newdir;
	t_cmd	cmd;

	cmd.io.out = 1;
	newdir = getenv("HOME");
	chdir(newdir);
	assert_pwd_cases(&cmd, newdir);
}
