#pragma once
#include "DECL.hpp"
#include "exec.hpp"
bool exec::DECL(Process& p) {
    const auto& b = p.module[p.pc];
    p.memory.declare(b.operand.at(0));
    return true;
}
