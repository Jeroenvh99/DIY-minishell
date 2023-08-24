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
// #include "msh.h"
// #include "msh_env.h"
// #include "msh_error.h"
// #include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

t_list	*glob_readdir(char const *path);

TestSuite(glob);

Test(glob, testwrap)
{
	glob_readdir("");
}