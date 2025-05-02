#include "POP.hpp"
#include "exec.hpp"

bool exec::POP(Process& p) {
    const auto& b = p.module[p.pc];
    if (p.stack.empty()) {
        p.err("Attempted to pop from an empty stack");
        return false;
    }

    auto value = p.stack.pop();
    if (!p.env_stack.set(b.operand.at(0), value)) {
        p.global_memory.set(b.operand.at(0), value);
    }
    return true;
}
