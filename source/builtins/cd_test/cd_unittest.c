# include <criterion/criterion.h>
# include <criterion/redirect.h>
# include <criterion/new/assert.h>
# include <criterion/new/memory.h>
# include <criterion/new/stream.h>
# include <criterion/alloc.h>
# include <criterion/abort.h>
# include <criterion/event.h>
# include <criterion/options.h>
# include <criterion/output.h>
# include <criterion/parameterized.h>
# include <criterion/stats.h>
# include <criterion/types.h>
# include "msh.h"
# include "libft.h"
# include <criterion/assert.h>
# include <criterion/internal/assert.h>

// Test(cd, no_arg_with_home)
// {
// 	t_msh	msh;
// 	t_cmd	cmd;

// 	char	*environ[] = {"HOME=/tmp/cd-no_arg_with_home", NULL};
// 	char	*input[] = {"cd", NULL};
// 	cmd.argv.array = input;
// 	msh.env = environ;

// 	system("mkdir /tmp/cd-no_arg_with_home");
// 	msh_cd(&cmd, &msh);
// 	//check if working directory changed
// 	system("rmdir /tmp/cd-no_arg_with_home");
// 	dict_destroy(&shell.env);
// }