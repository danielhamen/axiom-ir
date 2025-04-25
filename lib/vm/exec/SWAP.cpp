#pragma once
#include "SWAP.hpp"
#include "exec.hpp"
bool exec::SWAP(Process& p) {
    if (p.stack.size() < 2) return true;
    auto a = p.stack.pop();
    auto b = p.stack.pop();
    p.stack.push(a);
    p.stack.push(b);
    return true;
}
