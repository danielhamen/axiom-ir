#pragma once
#include "exec.hpp"
#include "RET.hpp"
bool exec::RET(Process& p) {
     if (p.callstack.empty()) throw std::runtime_error("Return without call");
     p.pc = p.callstack.pop();
     return true;
 }
