#include <string>
#include "CALL.hpp"
#include "exec.hpp"
bool exec::CALL(Process& p)  {
    p.env_stack.push_scope();

    const auto& b = p.module[p.pc];
    std::string nm = b.operand.at(0);
    if (nm.size()<2 || nm[0] != '.' || !p.labels.exists(nm.substr(1))) return false;
    p.callstack.push(p.pc + 1);
    p.pc = p.labels.get(nm.substr(1));
    return true;
}
