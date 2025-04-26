#include "DECL.hpp"
#include "exec.hpp"
bool exec::DECL(Process& p) {
    const auto& b = p.module[p.pc];
    if (!p.env_stack.empty())
        p.env_stack.declare(b.operand.at(0));
    else
        p.global_memory.declare(b.operand.at(0));
    return true;
}
