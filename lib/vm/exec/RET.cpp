#include "exec.hpp"
#include "RET.hpp"
bool exec::RET(Process& p) {
     if (p.callstack.empty()) throw std::runtime_error("Return without call");
     p.env_stack.pop_scope();    // drop callee’s locals
     p.pc = p.callstack.pop();
     return true;
 }
