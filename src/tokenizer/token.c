#include "../include/token.h"
#include "../include/operators.h"

#include "string.h"

struct nl_token nl_token_make(enum nl_token_type type, const char *value)
{
	struct nl_token token = {
		.type = type,
		.value = value
	};

	return token;
}

const char *parse_value(char terminator, int start, const char *src)
{
	char value[100] = {0};
	char current = src[start];

	int i = start;
	int char_count = 0;

	while (current != terminator && current != '\0')
	{
		value[i] = current;
		i++;

		current = src[i];
		char_count++;
	}

	return strdup(value);
}

struct nl_token nl_token_parse(int start, const char *src)
{
	struct nl_token token = {0};

	switch (src[start]) {
		case '=':
		case ':': {
			token = nl_op_parse(start, src);
			return token;
		}	
		case ' ': {
			token.type = NL_TOK_SPACE;
			token.value = " ";
			return token;
		}
		default: {
			const char *value = parse_value(' ', start, src);

			return nl_token_make(NL_TOKEN_IDENT, value);
		}
	}
}
