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
#include "libft.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

void	assert_token_str(char *str, t_toktype type)
{
    t_token	*tok;

    tok = token_init(str, type);
    cr_assert_eq(strcmp(tok->str, str), 0);
}

void	assert_token_type(char *str, t_toktype type)
{
    t_token	*tok;

    tok = token_init(str, type);
    cr_assert_eq(tok->type, type);
}

TestSuite(token);

Test(token, input_empty_0)
{
    char	*str = "echotest";
    t_toktype type = TOK_WORD;
    assert_token_str(str, type);
}

Test(token, input_empty_1)
{
    char	*str = "echotest";
    t_toktype type = TOK_WORD;
    assert_token_type(str, type);
}