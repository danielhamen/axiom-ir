#include "SET.hpp"
#include "exec.hpp"

bool exec::SET(Process& p) {
    const auto& b = p.module[p.pc];

    if (b.operand.empty()) {
        p.err("Missing operand in SET");
        return false;
    }

    const std::string& name = b.operand.at(0);

    if (p.stack.empty()) {
        p.err("SET failed: stack is empty");
        return false;
    }

    std::shared_ptr<Object> val = p.stack.back();

    // Try setting in env_stack first
    if (!p.env_stack.set(name, val)) {
        // If it doesn't exist in env_stack, set in global memory
        p.global_memory.set(name, val);
    }

    p.stack.pop();
    return true;
}
