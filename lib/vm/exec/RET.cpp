#include "exec.hpp"
#include "RET.hpp"
bool exec::RET(Process& p) {
     if (p.callstack.empty()) {
        p.err("Return without call");
        return false;
     }

     if (p.stack.empty()) {
        p.err("Attempted to return from empty stack");
        return false;
     }

     p.env_stack.pop_scope();    // drop callee’s locals
     p.pc = p.callstack.pop();
     return true;
 }
