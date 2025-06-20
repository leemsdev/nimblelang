#include "../include/tokenizer.h"
#include "stdlib.h"
#include <string.h>

/* TODO: Make an actual collection type to handle dyn resizing. */
struct nl_token* init_tokens_arr()
{
	int count = 10; 
	long memsize = sizeof(struct nl_token) * count;

	struct nl_token* tokens = calloc(count, memsize);

	return tokens;
}

struct nl_token* parse_src(const char *src)
{	
	struct nl_token* tokens = init_tokens_arr();

	int srclen = strlen(src);
	int i = 0;
	int token_count = 0;

	while (i < srclen) {
		struct nl_token token = nl_token_parse(i, src);

		i += strlen(token.value);

		tokens[token_count++] = token;
	}

	return tokens;
}

struct nl_token* nl_tokenize(const char *src)
{
	struct nl_token* tokens = parse_src(src);

	return tokens;
}

