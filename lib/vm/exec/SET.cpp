#include "SET.hpp"
#include "exec.hpp"
bool exec::SET(Process& p) {
    const auto& b = p.module[p.pc];
    if (!p.env_stack.set(b.operand.at(0), p.stack.back()))   // update if present
        p.global_memory.set(b.operand.at(0), p.stack.back()); // otherwise global
    p.stack.pop();
    return true;
}
