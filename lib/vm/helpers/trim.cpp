#include "trim.hpp"
#include <string>

std::string trim(const std::string &s) {
    auto a = std::find_if_not(s.begin(), s.end(), [](char c){ return std::isspace(c); });
    auto b = std::find_if_not(s.rbegin(), s.rend(), [](char c){ return std::isspace(c); }).base();
    return (b <= a ? std::string() : std::string(a, b));
}
