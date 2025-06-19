#ifndef TOKEN_H
#define TOKEN_H

enum nl_token_type {
	NL_TOKEN_IDENT,
	NL_TOK_EQ, 
	NL_TOK_COLON, 
	NL_TOK_COLON_EQ,
	NL_TOK_SPACE,
};

struct nl_token {
	enum nl_token_type type;
	const char* value;
};

struct nl_token nl_token_make(enum nl_token_type type, const char *value);
struct nl_token nl_token_parse(int start, const char *src);

#endif
