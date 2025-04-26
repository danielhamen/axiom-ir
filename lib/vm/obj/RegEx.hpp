#pragma once
#include "String.hpp"
#include <set>

class RegEx : public String {
public:
    std::set<char> flags;

    RegEx(const std::string& pattern, const std::set<char>& flags = {});

    std::string __name__() const override;

    bool has_flag(char flag) const;
};
