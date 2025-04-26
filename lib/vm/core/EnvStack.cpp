#include "EnvStack.hpp"
#include <stdexcept>

// --- Constructor ---
EnvStack::EnvStack() = default;

// --- Scope management ---
void EnvStack::push_scope() {
    scopes.emplace_back();
}

void EnvStack::pop_scope() {
    if (scopes.empty()) {
        throw std::runtime_error("EnvStack: Cannot pop from an empty scope stack.");
    }
    scopes.pop_back();
}

// --- Variable operations ---
void EnvStack::declare(const std::string& name) {
    if (scopes.empty()) {
        throw std::runtime_error("EnvStack: No local scope to declare variable '" + name + "'.");
    }
    scopes.back().declare(name);
}

bool EnvStack::set(const std::string& name, const std::shared_ptr<Object>& value) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->has(name)) {
            it->set(name, value);
            return true;
        }
    }
    return false; // Not found in any local scope
}

std::shared_ptr<Object> EnvStack::get(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->has(name)) {
            return it->get(name);
        }
    }
    throw std::runtime_error("EnvStack: Undefined variable '" + name + "'.");
}

bool EnvStack::has(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->has(name)) {
            return true;
        }
    }
    return false;
}


bool EnvStack::set_or_declare(const std::string& n,
                              const std::shared_ptr<Object>& v) {
    if (set(n, v)) return true;
    if (!scopes.empty()) { scopes.back().declare(n); scopes.back().set(n,v); }
    return true;
}

// --- Utility ---
bool EnvStack::empty() const {
    return scopes.empty();
}

size_t EnvStack::size() const {
    return scopes.size();
}
