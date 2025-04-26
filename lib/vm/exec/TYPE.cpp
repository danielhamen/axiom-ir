#include "TYPE.hpp"
bool exec::TYPE(Process& p) {
    Bytecode b = p.module.at(p.pc);
    if (b.operand.size() != 2) return false;

    auto& o1 = b.operand.at(0);
    auto& o2 = b.operand.at(1);

    if (
        o1.size() < 2 ||
        o1.at(0) != '$' ||
        !is_valid_identifier(o1.substr(1))
    ) return true;

    std::string iden = o1;
    std::string type = o2;

    return true;
}
