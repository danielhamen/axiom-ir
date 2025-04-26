#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../../vm/core/Memory.hpp"
#include "../../vm/obj/Object.hpp"

/**
 * EnvStack manages a stack of Memory scopes
 * for local variable environments (e.g., inside functions).
 */
class EnvStack {
public:
    EnvStack();

    // Scope management
    void push_scope();
    void pop_scope();

    // Variable operations
    void declare(const std::string& name);
    bool set(const std::string& name, const std::shared_ptr<Object>& value);
    std::shared_ptr<Object> get(const std::string& name) const;
    bool has(const std::string& name) const;
    bool set_or_declare(const std::string& name,
                        const std::shared_ptr<Object>& value);

    // Utility
    bool empty() const;
    size_t size() const;

private:
    std::vector<Memory> scopes;
};
