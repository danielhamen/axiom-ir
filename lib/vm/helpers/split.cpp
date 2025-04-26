#include <string>
#include <vector>
#include <sstream>
#include "split.hpp"
#include "trim.hpp"

std::vector<std::string> split(const std::string &s, char d)  {
    std::vector<std::string> out;
    std::istringstream ss(s);
    std::string item;
    while (std::getline(ss, item, d))
        if (!trim(item).empty())
            out.push_back(trim(item));
    return out;
}
