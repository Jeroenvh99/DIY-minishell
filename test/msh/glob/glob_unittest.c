// #include <criterion/criterion.h>
// #include <criterion/redirect.h>
// #include <criterion/new/assert.h>
// #include <criterion/new/memory.h>
// #include <criterion/new/stream.h>
// #include <criterion/alloc.h>
// #include <criterion/abort.h>
// #include <criterion/event.h>
// #include <criterion/options.h>
// #include <criterion/output.h>
// #include <criterion/parameterized.h>
// #include <criterion/stats.h>
// #include <criterion/types.h>
// #include "msh.h"
// #include "msh_env.h"
// #include "msh_error.h"
#include "libft.h"
#include "ft_glob.h"
// #include <criterion/assert.h>
// #include <criterion/internal/assert.h>

void	printlist(t_list *head)
{
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

void print_glob(t_ft_glob *glob_res)
{
	printlist(glob_res->globl);
}

// TestSuite(glob);

// Test(glob, testwrap)
// {
// 	glob_readdir("");
// }

int main()
{
	t_ft_glob glob_res;
	ft_glob(&glob_res, "*");
	print_glob(&glob_res);
}