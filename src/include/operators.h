#ifndef OPERATORS_H
#define OPERATORS_H

#include "token.h"

// ====================== 
//	Functions for parsing specific operators.
// ======================

struct nl_token nl_op_parse(int start, const char* src);

#endif

