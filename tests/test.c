#include "../src/include/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *tok_type_str(enum nl_token_type type)
{
	switch (type) {
		case NL_TOKEN_IDENT: return "identifier";
                case NL_TOK_EQ: return "equals";
		case NL_TOK_COLON: return "colon";
                case NL_TOK_COLON_EQ: return "colon equals";
		case NL_TOK_SPACE: return "space";
        }
}

void assert_token_is(enum nl_token_type type, struct nl_token token, const char* value)
{
	printf("\n\twant: Token(%s, %s) ", tok_type_str(type), value);
	if (type != token.type) {
		printf("\n\tToken type was not as expected. Wanted %s but got %s\n", tok_type_str(type), tok_type_str(token.type));
		exit(-1);
	}

	if (strcmp(value, token.value) != 0) {
		printf("\n\tValue was not as expected | wanted: %s, got: %s\n", value, token.value);
		exit(-1);
	}
	printf("=> ok");
};

void run_test(const char *name, void(*test_fn)())
{
	printf("TEST: %s => ", name);
	test_fn();
	printf("\n");
}

void test_ident()
{
	const char* inp = "hello";

	struct nl_token* tokens = nl_tokenize(inp);

	assert_token_is(NL_TOKEN_IDENT, tokens[0], "hello");
}

void test_colon_equals()
{
	// this should print out 5 tokens: equals, space, colon, space, colon equals
	const char *inp = "= : :=";

	struct nl_token* tokens = nl_tokenize(inp);

	assert_token_is(NL_TOK_EQ, tokens[0], "=");
	assert_token_is(NL_TOK_COLON, tokens[2], ":");
	assert_token_is(NL_TOK_COLON_EQ, tokens[4], ":=");
}

int main(void)
{
	run_test("Test Identifier", test_ident);
	run_test("Test Colon, Equals, Colon Equals", test_colon_equals);

	return 0;
}
