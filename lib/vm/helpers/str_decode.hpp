#pragma once
#include <string>

/**
 * Decodes a given string modifying the original string
 * e.g. str_decode("\"hello\n world!\"") becomes;
 * "hello
 *   world!"
 */
void str_decode(std::string& str);
