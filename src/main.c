#include "./strings/strings.h"
#include "./assert/assert.h"

int main(int argc, char *argv[]) {
	assert_msg(argc > 1, "Expected path to file", "");

	String src = string_from_file(argv[1]); 

	string_print(src);

	string_free(&src);

	string_assert_all_freed();
}
