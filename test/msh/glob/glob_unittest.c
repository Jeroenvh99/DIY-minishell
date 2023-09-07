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
#include "msh.h"
#include "msh_env.h"
#include "msh_error.h"
#include "libft.h"
#include "ft_glob.h"
// #include <criterion/assert.h>
// #include <criterion/internal/assert.h>

// void redirect_stdout(void)
// {
//     cr_redirect_stdout();
// }

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

// void assert_glob_output(char *in, char *expected)
// {
// 	t_ft_glob glob_res;
// 	ft_glob_init(&glob_res);
// 	ft_glob(&glob_res, in);
// 	print_glob(&glob_res);
// 	cr_assert_stdout_eq_str(expected);
// }

// TestSuite(glob, .init=redirect_stdout);

// Test(glob, testwrap)
// {
// 	assert_glob_output("", "");
// }

// Test(glob, testwrap)
// {
// 	assert_glob_output("*", "1\nhgfdhg\nhi.txt\n");
// }

int main() {
	t_ft_glob glob_res;
	ft_printf("test 1\n");
	ft_glob_init(&glob_res);
	ft_glob(&glob_res, "");
	print_glob(&glob_res);
	ft_printf("\n\ntest 2\n");
	ft_glob_init(&glob_res);
	ft_glob(&glob_res, "*");
	print_glob(&glob_res);
	ft_printf("\n\ntest 3\n");
	ft_glob_init(&glob_res);
	ft_glob(&glob_res, "hi");
	print_glob(&glob_res);
	ft_printf("\n\ntest 4\n");
	ft_glob_init(&glob_res);
	ft_glob(&glob_res, "?");
	print_glob(&glob_res);
	ft_glob_destroy(&glob_res);
}
