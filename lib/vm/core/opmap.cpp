#pragma once
#include "opmap.hpp"

const std::unordered_map<std::string, Opcode> opmap = {
    {"PUSH", OP_PUSH}, {"POP", OP_POP}, {"DUP", OP_DUP}, {"SWAP", OP_SWAP},
    {"DEL", OP_DEL}, {"DECL", OP_DECL}, {"SET", OP_SET}, {"GET", OP_GET},
    {"ADD", OP_ADD}, {"SUB", OP_SUB}, {"MUL", OP_MUL}, {"DIV", OP_DIV},
    {"MOD", OP_MOD}, {"EQ", OP_EQ}, {"LT", OP_LT}, {"GT", OP_GT},
    {"AND", OP_AND}, {"OR", OP_OR}, {"NOT", OP_NOT}, {"JMP", OP_JMP},
    {"JZ", OP_JZ}, {"JNZ", OP_JNZ}, {"CALL", OP_CALL}, {"RET", OP_RET},
    {"END", OP_END}, {"WRITE", OP_WRITE}, {"FLUSH", OP_FLUSH}, {"DUMP", OP_DUMP},
    {"IN", OP_IN}, {"FREAD", OP_FREAD}, {"FWRITE", OP_FWRITE}, {"EXIT", OP_EXIT},
    {"RAND", OP_RAND}, {"TIME", OP_TIME}, {"SLEEP", OP_SLEEP}, {"NOP", NOP}
};
