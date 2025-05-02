#include "GET.hpp"
#include "../helpers/parse_literal.hpp"
#include "exec.hpp"

bool exec::GET(Process& p) {
    const auto& b = p.module[p.pc];

    if (b.operand.empty()) {
        p.err("Missing operand in GET");
        return false;
    }

    const std::string& name = b.operand.at(0);
    std::shared_ptr<Object> val;

    if (p.env_stack.has(name)) {
        val = p.env_stack.get(name);
    } else if (p.global_memory.has(name)) {
        val = p.global_memory.get(name);
    } else {
        p.err("GET failed: variable not found → " + name);
        return false;
    }

    p.stack.push(val);
    return true;
}
