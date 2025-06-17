#pragma once

// ======================
// 
//	Assert helpers for debugging.
// 
// ======================

#include <stdbool.h>

void assert_msg(bool condition, const char* errmsg, const char* detail);
