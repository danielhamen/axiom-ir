#include <string>
#include "JMP.hpp"
#include "exec.hpp"

bool exec::JMP(Process& p) {
    const auto& b = p.module[p.pc];

    // Ensure operand exists
    if (b.operand.empty()) {
        p.err("Missing operand in JMP instruction");
        return false;
    }

    std::string nm = b.operand.at(0);

    // Try to jump to label as-is
    if (!p.labels.exists(nm)) {
        p.err("Unknown label in JMP: '" + nm + "'");
        return false;
    }

    // Perform the jump
    p.pc = p.labels.get(nm);
    return true;
}
