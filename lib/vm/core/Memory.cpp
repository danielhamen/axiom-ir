#include "Memory.hpp"
#include "string"
#include "../obj/Nix.hpp"

void Memory::declare(const std::string& n) {
    if (mem.find(n) != mem.end())
        throw std::runtime_error("Already declared: " + n);
    mem[n] = std::make_shared<Nix>();
}
void Memory::set(const std::string& n, const std::shared_ptr<Object>& v) {
    mem[n] = v;
}
void Memory::remove(const std::string& n) {
    auto it = mem.find(n);
    if (it == mem.end())
        throw std::runtime_error("Cannot erase undeclared variable: " + n);
    mem.erase(it);
}
const std::shared_ptr<Object>& Memory::get(const std::string& n) const {
    auto it = mem.find(n);
    if (it == mem.end())
        throw std::runtime_error("Undefined var: " + n);
    return it->second;
}
bool Memory::has(const std::string& n) const {
    auto it = mem.find(n);
    return it != mem.end();
}
