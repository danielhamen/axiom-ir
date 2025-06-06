#include <string>
#include "CALL.hpp"
#include "exec.hpp"
bool exec::CALL(Process& p) {
    const auto& b = p.module[p.pc];
    // Peek at what’s on the stack
    auto maybeFn = p.stack.pop();
    if (auto fnObj = std::dynamic_pointer_cast<FunctionObject>(maybeFn)) {
        // Let the function object handle binding new scope, args, etc.
        fnObj->invoke(p);
        return true;
    }

    if (b.operand.size() != 1) {
        p.err("CALL expects 1 operand, got " + std::to_string(b.operand.size()));
        return false;
    }
    const auto& nm = b.operand[0];
    if (!p.labels.exists(nm)) {
        p.err("Unknown label in CALL: '" + nm + "'");
        return false;
    }

    // 1) push a new local scope
    p.env_stack.push_scope();

    // 2) save return address (next instruction)
    p.callstack.push(p.pc + 1);

    // 3) jump into the function
    p.pc = p.labels.get(nm);
    return true;
}
