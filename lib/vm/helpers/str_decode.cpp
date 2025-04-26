#include "str_decode.hpp"

void str_decode(std::string& str) {
    if (!(str.starts_with('"') && str.ends_with('"')))
        throw "Invalid input string";

    str = str.substr(1, str.length() - 2);
    std::string result;
    result.reserve(str.size()); // Reserve enough memory to avoid reallocations

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\\' && i + 1 < str.size()) {
            char next = str[i + 1];
            switch (next) {
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
                case '\\': result += '\\'; break;
                case '"': result += '"'; break;
                case '\'': result += '\''; break;
                case '0': result += '\0'; break;
                default:
                    // Unknown escape: copy as-is
                    result += '\\';
                    result += next;
                    break;
            }
            ++i; // Skip the next character because it's part of escape
        } else {
            result += str[i];
        }
    }

    str = std::move(result); // Replace original string with decoded one
}
