#pragma once
#include <sstream>
#include <unordered_map>
#include <string>

template <typename K, typename V>
std::string unordered_map_to_string(const std::unordered_map<K, V>& umap);
