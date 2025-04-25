#pragma once
#include <string>
#include <vector>
#include "Opcode.hpp"

struct Bytecode {
    Opcode opcode;
    std::vector<std::string> operand;
    Bytecode(Opcode op, std::vector<std::string> o = {}) : opcode(op), operand(std::move(o)) {}
};
