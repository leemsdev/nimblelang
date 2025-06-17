#include "strings.h"
#include <stdio.h>
#include <stdlib.h>
#include "../assert/assert.h"
#include "../reader/reader.h"

#include "string.h"

#define STRING_MAX_ACTIVE 1024
#define STRING_FREED -1

// NOTE: No reclamation of strings is happening in here. So we will eventually reach a limit and explode. Fix :)

// All tracked strings
static char *active_strings[STRING_MAX_ACTIVE];
static int num_created = 0;

// This tracks the number of allocated strings that haven't been freed.
// Good for catching leaks.
static int num_active = 0;


// ======================
// Guards
// ======================

void assert_not_freed(const String str, const char* action) {
	assert_msg(str.location != STRING_FREED, "trying to perform action on a freed string", action);
}

void assert_valid_location(int location) {
	bool within_allowed_range = location >= 0 && location < STRING_MAX_ACTIVE;
	bool within_created_range = location < num_created; // num created is always 1 more than the actual index, cos zero-based index
	
	char num_str[20];
	sprintf(num_str, "loc: %d", location);

	assert_msg(within_allowed_range && within_created_range, "tried to get a string at an invalid location", num_str);
}

void assert_valid(const String str, const char* action) {
	assert_not_freed(str, action);
	assert_valid_location(str.location);
}

// ======================
// Private functions
// ======================

const char* get_data(const String str, const char* action) {
	assert_valid(str, action);

	char* data = active_strings[str.location];

	return data;
}

// ======================
// Exported functions
// ======================


String string_make(char* raw) {
	if (num_created >= STRING_MAX_ACTIVE) {
		printf("ERROR: cannot create string %s; would exceed string limit of %d", raw, STRING_MAX_ACTIVE);
		exit(1);
	}

	int next_location = num_created;

	active_strings[next_location] = strdup(raw);

	num_created++;
	num_active++;

	String str = {
		.location = next_location
	};

	return str;
}

void string_free(String *str) {
	assert_valid(*str, "tried to free");

	char *data = active_strings[str->location];

	free(data);

	str->location = STRING_FREED;
	active_strings[str->location] = NULL;

	num_active--;
}

void string_print(const String str) {
	const char *data = get_data(str, "tried to print");

	printf("%s", data);
}


String string_from_file(const char* path) {
	return string_make(reader_read_file(path));
}


void string_assert_all_freed() {
	char num_str[20];
	sprintf(num_str, "not freed: %d", num_active);

	assert_msg(num_active == 0, "Expected all strings to be freed, but was false", num_str);
}
