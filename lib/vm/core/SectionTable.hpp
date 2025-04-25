#pragma once
#include <unordered_map>
#include <string>

struct SectionTable {
    std::unordered_map<std::string, size_t> sections;
};
