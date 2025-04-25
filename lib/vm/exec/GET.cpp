#pragma once
#include "GET.hpp"
#include "../parse_literal.hpp"
#include "exec.hpp"
bool exec::GET(Process& p) {
    const auto& b = p.module[p.pc];
    p.stack.push(parse_literal(b.operand.at(0)));
    return true;
}
