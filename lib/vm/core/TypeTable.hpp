#include <string>
#include <unordered_map>
struct TypeTable {
    std::unordered_map<std::string, std::string> types;
    void set(const std::string& name, const std::string& type);
    std::string get(const std::string& name) const;
    bool has(const std::string& name) const;
};
