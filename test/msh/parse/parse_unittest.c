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
#include <signal.h>
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

void	assert_token_to_str(t_token *token, char *expected)
{
    char	*str;

    str = token_to_str(token);
    cr_assert_eq(strcmp(str, expected), 0);
}

void	assert_token_freed(t_token *token)
{
    token_to_str(token);
    token->str = "ha, this doesn't work";
}

TestSuite(parse);

Test(parse, token_str_0)
{
    t_token token;
    token.str = "hi test";
    assert_token_to_str(&token, "hi test");
}

Test(parse, token_str_1, .signal = SIGSEGV)
{
    t_token token;
    token.str = "hi test";
    assert_token_to_str(&token, "hi test");
}
