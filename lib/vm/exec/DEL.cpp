#include "DEL.hpp"
#include "exec.hpp"
bool exec::DEL(Process& p) {
    const auto& b = p.module[p.pc];
    if (p.env_stack.has(b.operand.at(0)))
        p.env_stack.pop_scope();            // optional: or implement remove()
    else
        p.global_memory.remove(b.operand.at(0));
    return true;
}
