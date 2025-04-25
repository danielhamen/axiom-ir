#pragma once
#include "PUSH.hpp"
#include "../helpers/parse_literal.hpp"
#include "exec.hpp"
bool exec::PUSH(Process& p) {
    const auto& b = p.module[p.pc];
    p.stack.push(parse_literal(b.operand.at(0)));
    return true;
}
