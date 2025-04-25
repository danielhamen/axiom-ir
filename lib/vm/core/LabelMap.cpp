#include "LabelMap.hpp"

void LabelMap::set(std::string label, size_t pc) {
    labels[label] = pc;
}

size_t LabelMap::get(std::string label) {
    return labels[label];
}

bool LabelMap::exists(std::string label) {
    return labels.contains(label);
}
