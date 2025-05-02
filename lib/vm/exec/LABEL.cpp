#include <string>
#include "LABEL.hpp"
#include "exec.hpp"
#include "../helpers/is_valid_identifier.hpp"

// New helper for namespaced label validation
bool is_valid_namespaced_identifier(const std::string& name) {
    // Split by '.'
    size_t start = 0;
    while (start < name.size()) {
        size_t dot = name.find('.', start);
        std::string part = name.substr(start, dot - start);
        if (!is_valid_identifier(part))
            return false;
        if (dot == std::string::npos)
            break;
        start = dot + 1;
    }
    return true;
}

bool exec::LABEL(Process& p) {
    const auto& b = p.module[p.pc];
    std::string name = b.operand.at(0);

    // No longer require leading '.', but ensure name is valid
    if (!is_valid_namespaced_identifier(name)) {
        p.err("Invalid label name: " + name);
        return false;
    }

    // Store label exactly as-is (e.g., "Math.Linear.dot")
    p.labels.set(name, p.pc + 1);
    return true;
}
