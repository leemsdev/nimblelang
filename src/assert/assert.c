#include "assert.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void assert_msg(bool condition, const char* errmsg, const char* detail) {
	if (condition == false) {
		printf("ASSERT FAIL: %s\ndetail: %s\n", errmsg, detail);
		exit(1);
	}
}
