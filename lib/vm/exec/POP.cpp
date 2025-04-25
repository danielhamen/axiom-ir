#pragma once
#include "POP.hpp"
#include "exec.hpp"
bool exec::POP(Process& p) {
    const auto& b = p.module[p.pc];
    p.memory.set(b.operand.at(0), p.stack.pop());
    return true;
}
