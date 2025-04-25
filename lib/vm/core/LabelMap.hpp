#include <unordered_map>
#include <string>

struct LabelMap {
    std::unordered_map<std::string, size_t> labels = {};
    void set(std::string label, size_t pc);

    size_t get(std::string label);

    bool exists(std::string label);
};
