#ifndef TOKEN_H
#define TOKEN_H

enum nl_token_type {
	/* Identifiers and Keywords */
	NL_TOK_IDENT,

	/* Assignment Operators */
	NL_TOK_EQ, 
	NL_TOK_COLON, 
	NL_TOK_COLON_EQ,

	/* Math Operators */
	NL_TOK_PLUS,
	NL_TOK_PLUS_PLUS,

	/* Whitespace */
	NL_TOK_SPACE,

	/* Numbers */
	NL_TOK_INT
};

struct nl_token {
	enum nl_token_type type;
	const char* value;
};

struct nl_token nl_token_make(enum nl_token_type type, const char *value);
struct nl_token nl_token_parse(int start, const char *src);

#endif
