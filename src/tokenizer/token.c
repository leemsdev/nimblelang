#include "../include/token.h"
#include "../include/operators.h"

#include "string.h"
#include <stdbool.h>
#include <stdio.h>

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
	char c = src[start];

	size_t i = start;
	size_t count = 0;

	while (c != terminator && c != '\0')
	{
		value[count] = c;
		i++;
		count++;
		c = src[i];

	}

	return strdup(value);
}

struct nl_token parse_digit(int start, const char *src)
{
	struct nl_token token = {
		.type = NL_TOK_INT,
		.value = ""
	};

	char v[100] = {0};
	char c = src[start];

	size_t count = 0;
	size_t i = start;

	while (c >= '0' && c <= '9' && c != ' ') {
		v[count] = c;
		i++;
		count++;
		c = src[i];
	}

	token.value = strdup(v);

	return token;
}

struct nl_token nl_token_parse(int start, const char *src)
{
	struct nl_token token = {0};
	const char c = src[start];

	if (c >= '0' && c <= '9') {
		return parse_digit(start, src);	
	};

	switch (c) {
		case '=':
		case ':':
		case '+': {
			return nl_op_parse(start, src);
		}	
		case ' ': {
			token.type = NL_TOK_SPACE;
			token.value = " ";
			return token;
		}
		default: {
			const char *value = parse_value(' ', start, src);

			return nl_token_make(NL_TOK_IDENT, value);
		}
	}
}
