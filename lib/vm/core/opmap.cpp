#include "opmap.hpp"
#include <stdexcept>

const std::unordered_map<std::string, Opcode> opmap = {
    {"PUSH", OP_PUSH}, {"POP", OP_POP}, {"DUP", OP_DUP}, {"SWAP", OP_SWAP},
    {"DEL", OP_DEL}, {"DECL", OP_DECL}, {"SET", OP_SET}, {"GET", OP_GET},
    {"ADD", OP_ADD}, {"SUB", OP_SUB}, {"MUL", OP_MUL}, {"DIV", OP_DIV},
    {"MOD", OP_MOD}, {"EQ", OP_EQ}, {"LT", OP_LT}, {"GT", OP_GT},
    {"AND", OP_AND}, {"OR", OP_OR}, {"NOT", OP_NOT}, {"JMP", OP_JMP},
    {"JZ", OP_JZ}, {"JNZ", OP_JNZ}, {"CALL", OP_CALL}, {"RET", OP_RET},
    {"END", OP_END}, {"WRITE", OP_WRITE}, {"FLUSH", OP_FLUSH}, {"DUMP", OP_DUMP},
    {"IN", OP_IN}, {"FREAD", OP_FREAD}, {"FWRITE", OP_FWRITE}, {"EXIT", OP_EXIT},
    {"RAND", OP_RAND}, {"TIME", OP_TIME}, {"SLEEP", OP_SLEEP}, {"NOP", NOP},
    {"TYPE", OP_TYPE}, {"CAST", OP_CAST}, {"LABEL", OP_LABEL}
};


// Define reverse mappings from Opcode → string
const std::unordered_map<Opcode, std::string> strmap = [] {
    std::unordered_map<Opcode, std::string> rev;
    for (const auto& [key, val] : opmap) {
        rev[val] = key;
    }
    return rev;
}();

// Lookup function: string → Opcode
const Opcode get_opcode_from_string(const std::string& opcode) {
    auto it = opmap.find(opcode);
    if (it != opmap.end())
        return it->second;
    throw std::invalid_argument("Unknown opcode: " + opcode);
}

// Lookup function: Opcode → string
const std::string get_string_from_opcode(Opcode opcode) {
    auto it = strmap.find(opcode);
    if (it != strmap.end())
        return it->second;
    return "UNKNOWN";
}
