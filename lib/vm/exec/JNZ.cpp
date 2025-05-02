#include <string>
#include "JNZ.hpp"
#include "exec.hpp"

bool exec::JNZ(Process& p) {
    auto cond = p.stack.pop();
    const auto& nm = p.module[p.pc].operand.at(0);

    if (!cond->__bool__()) {
        if (!p.labels.exists(nm)) {
            p.err("Unknown label in JNZ: '" + nm + "'");
            return false;
        }
        p.pc = p.labels.get(nm);
    }

    return true;
}
