#include "../src/include/tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *tok_type_str(enum nl_token_type type)
{
	switch (type) {
		case NL_TOK_IDENT: return "identifier";
                case NL_TOK_EQ: return "equals";
		case NL_TOK_COLON: return "colon";
                case NL_TOK_COLON_EQ: return "colon equals";
		case NL_TOK_SPACE: return "space";
                case NL_TOK_PLUS: return "plus";
		case NL_TOK_PLUS_PLUS: return "plus plus";
		case NL_TOK_INT: return "int";
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
	struct nl_token* tokens = nl_tokenize("hello");

	assert_token_is(NL_TOK_IDENT, tokens[0], "hello");
}

void test_colon_equals()
{
	// this should print out 5 tokens: equals, space, colon, space, colon equals
	struct nl_token* tokens = nl_tokenize("= : :=");

	assert_token_is(NL_TOK_EQ, tokens[0], "=");
	assert_token_is(NL_TOK_COLON, tokens[2], ":");
	assert_token_is(NL_TOK_COLON_EQ, tokens[4], ":=");
}

void test_plus_plusplus()
{
	// plus, space, plusplus
	struct nl_token* tokens = nl_tokenize("+ ++");

	assert_token_is(NL_TOK_PLUS, tokens[0], "+");
	assert_token_is(NL_TOK_PLUS_PLUS, tokens[2], "++");
}

void test_int()
{
	struct nl_token* tokens = nl_tokenize("3 1 13 12837");

	assert_token_is(NL_TOK_INT, tokens[0], "3");
	assert_token_is(NL_TOK_INT, tokens[2], "1");
	assert_token_is(NL_TOK_INT, tokens[4], "13");
	assert_token_is(NL_TOK_INT, tokens[6], "12837");
}

void test_arith_expr() 
{
 	struct nl_token* tokens = nl_tokenize("x := 3 + 10");

	assert_token_is(NL_TOK_IDENT, tokens[0], "x");
	assert_token_is(NL_TOK_SPACE, tokens[1], " ");
	assert_token_is(NL_TOK_COLON_EQ, tokens[2], ":=");
	assert_token_is(NL_TOK_SPACE, tokens[3], " ");
	assert_token_is(NL_TOK_INT, tokens[4], "3");
	assert_token_is(NL_TOK_SPACE, tokens[5], " ");
	assert_token_is(NL_TOK_PLUS, tokens[6], "+");
	assert_token_is(NL_TOK_SPACE, tokens[7], " ");
	assert_token_is(NL_TOK_INT, tokens[8], "10");
}

/* TODO: Implement */
void test_float() {
	struct nl_token* tokens = nl_tokenize("3.0 5.0 1.25");
}

int main(void)
{
	run_test("Test Identifier", test_ident);
	run_test("Test Colon, Equals, Colon Equals", test_colon_equals);
	run_test("Test Plus, PlusPlus", test_plus_plusplus);
	run_test("Test Int", test_int);
	run_test("Arithmetic expr", test_arith_expr);
	// run_test("Test float", test_float);

	printf("\nAll tests passed\n");

	return 0;
}
