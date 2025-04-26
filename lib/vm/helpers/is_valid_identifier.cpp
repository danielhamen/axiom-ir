#include <regex>
#include "is_valid_identifier.hpp"

bool is_valid_identifier(const std::string& s) {
    static const std::regex expr("^[a-zA-Z_][a-zA-Z_0-9]*$");
    return std::regex_match(s, expr);
}
