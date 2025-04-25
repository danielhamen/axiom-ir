#pragma once
#include "unordered_map_to_string.hpp"

template <typename K, typename V>
std::string unordered_map_to_string(const std::unordered_map<K, V>& umap) {
    std::stringstream ss;
    ss << "{";
    for (const auto& pair : umap) {
        ss << "\"" << pair.first << "\":\"" << pair.second << "\",";
    }

    std::string result = ss.str();
    if (result.length() > 1) {
        result.pop_back(); // Remove the trailing comma
    }
    result += "}";
    return result;
}
