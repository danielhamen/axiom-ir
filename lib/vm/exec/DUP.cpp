#pragma once
#include "DUP.hpp"
#include "exec.hpp"
bool exec::DUP(Process& p)  {
    if (p.stack.empty()) return true;
    p.stack.push(p.stack.back());
    return true;
}
