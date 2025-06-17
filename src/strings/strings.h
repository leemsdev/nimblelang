#pragma once

// ======================
// 
//	Functions for creating and releasing strings.
//
//	String structs expose a location and a length. The actual string data is stored in a private array inside `strings.c`.
//	This is intended to enforce access only through functions exported from this file, which implements guards and checks to
//	avoid bad access, double frees, etc.
//	We also track the number of strings that have been allocated but not freed, which is good for preventing leaks.
// 
// ======================

typedef struct  {
	int location;
} String;

String string_make(char* raw);
void string_free(String *str);
void string_print(const String str);
String string_from_file(const char* path);

void string_assert_all_freed();
