#include "reader.h"

// =========================
// 
//	Implements the functions defined in reader.h.
//	Reads file contents into buffer.
//
//	You should probably use this via the string module, as that
//	provides better memory safety.
//
// =========================

#include <stdio.h>
#include <stdlib.h>
#include "../assert/assert.h"

long read_file_size(FILE *file_ptr) {
	fseek(file_ptr, 0, SEEK_END);

	long file_size = ftell(file_ptr);

	rewind(file_ptr);

	return file_size;
}

char *reader_read_file(const char *path) {
	FILE *file_ptr = fopen(path, "r");

	assert_msg(file_ptr != NULL, "Couldn't open src file", path);

	long file_size = read_file_size(file_ptr);

	assert_msg(file_size > 0, "File cannot be empty", path);

	// 1 extra byte. Small one. Tiny lil byte. I'm so hungry.	
	char *file_buffer = malloc(file_size + 1);

	size_t bytes_read = fread(file_buffer, 1, file_size, file_ptr);
	assert_msg(bytes_read == file_size, "Did not read expected file size", path);

	// Terminate that bad boy
	file_buffer[file_size] = '\0';

	fclose(file_ptr);
	
	return file_buffer;
}
