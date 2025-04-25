#pragma once
#include <string>
#include "LABEL.hpp"
#include "exec.hpp"
#include "../helpers/is_valid_identifier.cpp"
bool exec::LABEL(Process& p)  {
    const auto& b = p.module[p.pc];
    std::string name = b.operand.at(0);
    if (name.size() < 2 || name[0] != '.' || !is_valid_identifier(name.substr(1)))
        return false;
    p.labels.set(name.substr(1), p.pc + 1);
    return true;
}
