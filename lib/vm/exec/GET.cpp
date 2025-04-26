#include "GET.hpp"
#include "../helpers/parse_literal.hpp"
#include "exec.hpp"
bool exec::GET(Process& p) {
    const auto& b = p.module[p.pc];
    std::shared_ptr<Object> val;
    if (p.env_stack.has(b.operand.at(0)))
        val = p.env_stack.get(b.operand.at(0));
    else
        val = p.global_memory.get(b.operand.at(0));
    p.stack.push(val);
    return true;
}
