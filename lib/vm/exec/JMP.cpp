#pragma once
#include <string>
#include "JMP.hpp"
#include "exec.hpp"
bool exec::JMP(Process& p) {
    const auto& b = p.module[p.pc];
    std::string nm = b.operand.at(0);
    if (nm.size() < 2 || nm[0] != '.' || !p.labels.exists(nm.substr(1)))
        return false;
    p.pc = p.labels.get(nm.substr(1));
    return true;
}
