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
#include "msh_parse.h"
#include "msh_error.h"
#include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

void	printlist(t_list *head)
{
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

void	printlist_toktype(t_list *head)
{
	while (head)
	{
		ft_printf("%i\n", head->type);
		head = head->next;
	}
}

assert_lex_len(char *in, int expected)
{
	t_list	*tokens;

	tokens = NULL;
	lex(&tokens, in);
	cr_assert_eq(list_size(tokens), expected);
}

assert_lex_tok_str(char *in, char *expected)
{
	t_list	*tokens;

	tokens = NULL;
	lex(&tokens, in);
	printlist(tokens);
	cr_assert_stdout_eq(expected);
}

assert_lex_tok_type(char *in, char *expected)
{
	t_list	*tokens;

	tokens = NULL;
	lex(&tokens, in);
	printlist_toktype(tokens);
	cr_assert_stdout_eq(expected);
}

assert_lex_status(char *in, int expected)
{
	t_list	*tokens;
	int stat;

	tokens = NULL;
	stat = lex(&tokens, in);
	cr_assert_eq(stat, expected);
}

assert_lex_incomplete(char *in)
{
	t_list	*tokens;

	tokens = NULL;
	lex(&tokens, in);
	cr_assert_lt(list_last(tokens)->type, 0);
}

TestSuite(lex);

Test(lex, input_empty_0)
{
	char *str = "";
	assert_lex_len(str, 0);
}

Test(lex, input_empty_1)
{
	char *str = "";
	assert_lex_status(str, MSH_SUCCESS);
}

Test(lex, input_one_0)
{
	char *str = "\'\t\'\'";
	assert_lex_len(str, 1);
}

Test(lex, input_one_1)
{
	char *str = "\'\t\'\'";
	assert_lex_incomplete(str);
}

Test(lex, input_one_2)
{
	char *str = "\'\t\'\'";
	char *expected = "\'\t\'\'\n";
	assert_lex_tok_str(str, expected);
}

Test(lex, input_one_3)
{
	char *str = "\'\t\'\'";
	char *expected = "-1\n";
	assert_lex_tok_type(str, expected);
}

Test(lex, input_one_4)
{
	char *str = "\'\t\'\'";
	assert_lex_status(str, MSH_INCOMPLETE_TOKEN);
}

Test(lex, input_six_0)
{
	char *str = "jedes fahrrad sollte eine klingel haben";
	assert_lex_len(str, 6);
}

Test(lex, input_six_1)
{
	char *str = "jedes fahrrad sollte eine klingel haben";
	char *expected = "jedes\nfahrrad\nsollte\neine\nklingel\nhaben\n";
	assert_lex_tok_str(str, expected);
}

Test(lex, input_six_2)
{
	char *str = "jedes fahrrad sollte eine klingel haben";
	char *expected = "0\n0\n0\n0\n0\n0\n";
	assert_lex_tok_type(str, expected);
}

Test(lex, input_six_3)
{
	char *str = "jedes fahrrad sollte eine klingel haben";
	assert_lex_status(str, MSH_SUCCESS);
}

Test(lex, input_incomplete_0)
{
	char *str = "jedes \"";
	assert_lex_incomplete(str);
}

Test(lex, input_incomplete_1)
{
	char *str = "jedes \"";
	char *expected = "jedes\n\"\n";
	assert_lex_tok_str(str, expected);
}

Test(lex, input_incomplete_2)
{
	char *str = "jedes \"";
	char *expected = "0\n-2\n";
	assert_lex_tok_type(str, expected);
}

Test(lex, input_incomplete_3)
{
	char *str = "jedes \"";
	assert_lex_len(str, 2);
}

Test(lex, input_incomplete_4)
{
	char *str = "jedes \"";
	assert_lex_status(str, MSH_INCOMPLETE_TOKEN);
}

Test(lex, input_incomplete_5)
{
	char *str = "jedes \'";
	assert_lex_incomplete(str);
}

Test(lex, input_incomplete_6)
{
	char *str = "jedes \'";
	char *expected = "jedes\n\'\n";
	assert_lex_tok_str(str, expected);
}

Test(lex, input_incomplete_7)
{
	char *str = "jedes \'";
	char *expected = "0\n-1\n";
	assert_lex_tok_type(str, expected);
}

Test(lex, input_incomplete_8)
{
	char *str = "jedes \'";
	assert_lex_len(str, 2);
}

Test(lex, input_incomplete_9)
{
	char *str = "jedes \'";
	assert_lex_status(str, MSH_INCOMPLETE_TOKEN);
}

Test(lex, input_incomplete_10)
{
	char *str = "\'\"\'\"\'\"\'";
	assert_lex_status(str, MSH_INCOMPLETE_TOKEN);
}

Test(lex, input_incomplete_11)
{
	char *str = "\'\"\'\"\'\"\'";
	assert_lex_incomplete(str);
}

Test(lex, input_incomplete_12)
{
	char *str = "\'\"\'\"\'\"\'";
	assert_lex_len(str, 1);
}

Test(lex, input_incomplete_13)
{
	char *str = "\'\"\'\"\'\"\'";
	char *expected = "\'\"\'\"\'\"\'\n";
	assert_lex_tok_str(str, expected);
}

Test(lex, input_incomplete_14)
{
	char *str = "\'\"\'\"\'\"\'";
	char *expected = "-1\n";
	assert_lex_tok_type(str, expected);
}

Test(lex, input_incomplete_15)
{
	char *str = "\"\'\"\'\"\'\"";
	assert_lex_status(str, MSH_INCOMPLETE_TOKEN);
}

Test(lex, input_incomplete_16)
{
	char *str = "\"\'\"\'\"\'\"";
	assert_lex_incomplete(str);
}

Test(lex, input_incomplete_17)
{
	char *str = "\"\'\"\'\"\'\"";
	assert_lex_len(str, 1);
}

Test(lex, input_incomplete_18)
{
	char *str = "\"\'\"\'\"\'\"";
	char *expected = "\"\'\"\'\"\'\"\n";
	assert_lex_tok_str(str, expected);
}

Test(lex, input_incomplete_19)
{
	char *str = "\"\'\"\'\"\'\"";
	char *expected = "-2\n";
	assert_lex_tok_type(str, expected);
}
