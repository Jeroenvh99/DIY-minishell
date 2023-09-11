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
#include "msh_error.h"
#include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <stdio.h>

void redirect_stdout(void)
{
    cr_redirect_stdout();
}

void	printlist(t_list *head)
{
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

// void	printlist_err(t_list *head)
// {
// 	while (head)
// 	{
// 		ft_dprintf(2, "%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// }

void assert_expand_str(char *str, char *expected, void (*env_init)(t_msh *))
{
	t_msh msh;
	t_list *words;

	words = NULL;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	expand(&words, &str, &msh);
	printf("%s", str);
	// dprintf(2, "%s", str);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void assert_expand_words(char *str, char *expected, void (*env_init)(t_msh *))
{
	t_msh msh;
	t_list *words;

	words = NULL;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	expand(&words, &str, &msh);
	printlist(words);
	// printlist_err(words);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}

void assert_expand_status(char *str, int expected, void (*env_init)(t_msh *))
{
	t_msh msh;
	int status;
	t_list *words;

	words = NULL;
	bzero(&msh, sizeof(msh));
	env_init(&msh);
	status = expand(&words, &str, &msh);
	cr_assert_eq(status, expected);
}

void	env_with_home(t_msh *msh)
{
	char	*env_sub[] = {"HOME=/Users/jvan-hal", "LOGNAME=jvan-hal", "OLDPWD=/tmp/cd-dash", NULL};
    env_init(&msh->env, env_sub);
}

void	env_without_home(t_msh *msh)
{
	char	*env_sub[] = {"LOGNAME=jvan-hal", "OLDPWD=/tmp/cd dash", NULL};
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
	char *in = ft_strdup("$HOME");
	char *expected = "/Users/jvan-hal";
	assert_expand_str(in, expected, &env_with_home);
}

Test(expand, input_one_1)
{
	char *in = ft_strdup("$HOME");
	assert_expand_status(in, MSH_SUCCESS, &env_with_home);
}

Test(expand, input_one_2)
{
	char *in = ft_strdup("\"$OLDPWD\"");
	char *expected = "\"/tmp/cd dash\"";
	assert_expand_str(in, expected, &env_without_home);
}

Test(expand, input_one_3)
{
	char *in = ft_strdup("\"$OLDPWD\"");
	char *expected = "/tmp/cd dash\n";
	assert_expand_words(in, expected, &env_without_home);
}

Test(expand, input_one_4)
{
	char *in = ft_strdup("\'$OLDPWD\'");
	char *expected = "\'$OLDPWD\'";
	assert_expand_str(in, expected, &env_without_home);
}

Test(expand, input_one_5)
{
	char *in = ft_strdup("\'$OLDPWD\'");
	char *expected = "$OLDPWD\n";
	assert_expand_words(in, expected, &env_without_home);
}

Test(expand, input_one_6)
{
	char *in = ft_strdup("$OLDPWD");
	char *expected = "dash\n/tmp/cd\n";
	assert_expand_words(in, expected, &env_without_home);
}

Test(expand, input_one_7)
{
	char *in = ft_strdup("$LANG");
	char *expected = "";
	assert_expand_str(in, expected, &env_with_home);
}

Test(expand, input_one_8)
{
	char *in = ft_strdup("$LANG");
	assert_expand_status(in, MSH_SUCCESS, &env_with_home);
}

Test(expand, input_one_9)
{
	char *in = ft_strdup("b$LANG");
	char *expected = "b";
	assert_expand_str(in, expected, &env_with_home);
}

Test(expand, input_one_10)
{
	char *in = ft_strdup("hi this is a test");
	char *expected = "hi this is a test";
	assert_expand_str(in, expected, &env_with_home);
}

Test(expand, input_one_11)
{
	char *in = ft_strdup("hi this is a test");
	char *expected = "hi this is a test\n";
	assert_expand_words(in, expected, &env_with_home);
}
