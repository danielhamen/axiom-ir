#include "TypeTable.hpp"
std::unordered_map<std::string, std::string> types;

void TypeTable::set(const std::string& name, const std::string& type) {
    types[name] = type;
}

std::string TypeTable::get(const std::string& name) const {
    auto it = types.find(name);
    if (it == types.end()) return "any";
    return it->second;
}

bool TypeTable::has(const std::string& name) const {
    return types.find(name) != types.end();
}
