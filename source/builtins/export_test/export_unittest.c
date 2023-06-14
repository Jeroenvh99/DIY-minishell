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

void redirect_stderr(void)
{
    cr_redirect_stderr();
}

void	assert_cd_env(t_cmd *cmd, const char *name, void (*env_init)(t_msh *))
{
	t_msh	msh;

	cmd->io.out = 1;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	msh_cd(cmd, &msh);
	// print_env(msh.env.envp);
	cr_assert_not_null(env_search(&msh.env, name));
    env_free_(&msh.env);
}
