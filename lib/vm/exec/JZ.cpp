#pragma once
#include <string>
#include "JZ.hpp"
#include "exec.hpp"
bool exec::JZ(Process& p) {
    auto cond = p.stack.pop();
    const auto& b = p.module[p.pc];
    std::string nm = b.operand.at(0);
    if (cond->__bool__()) {
        if (nm.size() >= 2 && nm[0]=='.' && p.labels.exists(nm.substr(1)))
            p.pc = p.labels.get(nm.substr(1));
        else return false;
    }
    return true;
}
