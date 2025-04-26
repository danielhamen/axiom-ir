#include "RegEx.hpp"

RegEx::RegEx(const std::string& pattern, const std::set<char>& f)
    : String(pattern), flags(f) {}

std::string RegEx::__name__() const {
    return "string::regex";
}

bool RegEx::has_flag(char flag) const {
    return flags.find(flag) != flags.end();
}
