//
//  string.h
//  AoC2022
//
//  Created by Anders Runesson on 2022-12-25.
//

#ifndef string_h
#define string_h

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>

#include "list.h"

struct string {
    size_t len;
    char* c_str;
};

#define STRING_LEN(str) (str->len + sizeof(struct string))

/// Allocate string object with len size. Len includes terminating \0, and thus must be at least 1.
/// - Parameter len: Length of character buffer, in bytes. It is an error to use 0 len.
/// - Returns: `struct string*` object with allocated buffer, initialized to \0.
struct string* allocString(size_t len);

/// Allocate string object and copies data into character buffer of `len` size. `len` includes terminating \0.
/// If \0 is found before `len` bytes have been copied, the remainder of the buffer will be initialized to \0.
/// if `len` is less than length of `data` (no \0 is found) then  only `len` - 1 characters will be copied to buffer, and the last character will be set to \0.
/// - Parameter len: Size of byte buffer, including terminating \0
/// - Parameter data: Character array that will be copied, as-is, to allocated memory buffer
struct string* initString(size_t len, const char* data);

/// Deallocate string and character buffer
///  - Parameter str: String object to be deallocated.
void releaseString(struct string* str);

/// Replace all occurrences of find with replaceWith and return a new string.
///  - Parameter str: `struct string*` object to search in
///  - Parameter find: Character to find in `str`
///  - Parameter replaceWith: This character will be written over find in `str`
///  - Returns: New string object with `find` replaced by `replaceWith`
struct string* replaceInString(const struct string* str, char find, char replaceWith);

/// Returns a pointer to first occurrence of `c`, in `str`
/// - Parameter str: `struct string*` object to search in
/// - Parameter c: `char` to search for in `str`
/// - Returns: `char*` pointing to first occurence of `c` in `str`, or NULL if not found
char* findCharInString(const struct string* str, char c);

/// Returns the first index in string containing c.
/// - Parameter str: `struct string*` object to search in
/// - Parameter c: `char` to search for in `str`
/// - Returns: index of first occurence of `c` in `str`, or -1 if not found
int findIndexInString(const struct string* str, char c);

/// Split `str` into list of sub strings at `separator`. Return first entry in a list of substrings.
///  - Parameter str: String object to split
///  - Parameter separator: Character to delimit strings
///  - Returns: `struct list*` containing all string splits
const struct list* splitString(const struct string* str, char separator);

#endif /* string_h */
