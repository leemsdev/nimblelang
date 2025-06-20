#include "../include/operators.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char char_at(int pos, const char *src)
{
	if (pos >= strlen(src)) 
		return EOF;

	return src[pos];
}

struct nl_token nl_op_parse(int start, const char *src)
{
	char current = src[start];

	switch (current) {
		case '=': {
			return nl_token_make(NL_TOK_EQ, "=");
		}

		case ':': {
			if (char_at(start + 1, src) == '=') {
				return nl_token_make(NL_TOK_COLON_EQ, ":=");
			}
			
			return nl_token_make(NL_TOK_COLON, ":");
		}

		case '+': {
			if (char_at(start + 1, src) == '+') {
				return nl_token_make(NL_TOK_PLUS_PLUS, "++");
			}

			return nl_token_make(NL_TOK_PLUS, "+");
		}

		default: {
			printf("\nInvalid character passed to nl_op_parse: %c\n", current);
			exit(-1);
		}	
	}
}
