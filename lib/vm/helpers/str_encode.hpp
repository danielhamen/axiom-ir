#pragma once
#include <string>

/**
 * Encodes a given string modifying the original string
 * e.g. str_decode("\"hello\n world!\"") becomes;
 * \\"hello\\nworld!\\"
 */
void str_encode(std::string& str);
