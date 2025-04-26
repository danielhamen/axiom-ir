#include "Bytecode.hpp"
#include "opmap.hpp"

std::string Bytecode::toString() {
    std::string opname = "UNDEFINED_OP_CODE";
    for (auto kv : opmap) {
        if (kv.second == opcode) {
            opname = kv.first;
        }
    }

    std::string out = "(" + opname + ",";
    for (auto o : operand) {
        out += o + ",";
    }

    return out.substr(0, out.size() - 1) + ")";
}
