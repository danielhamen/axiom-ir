#pragma once
#include "SET.hpp"
#include "exec.hpp"
bool exec::SET(Process& p) {
    const auto& b = p.module[p.pc];
    p.memory.set(b.operand.at(0), p.stack.pop());
    return true;
}
