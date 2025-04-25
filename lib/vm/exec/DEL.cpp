#pragma once
#include "DEL.hpp"
#include "exec.hpp"
bool exec::DEL(Process& p) {
    const auto& b = p.module[p.pc];
    p.memory.remove(b.operand.at(0));
    return true;
}
