#pragma once
#include <unordered_map>
#include <string>
#include "Opcode.hpp"

extern const std::unordered_map<std::string, Opcode> opmap;

extern const Opcode get_opcode_from_string(const std::string& opcode);
extern const std::string get_string_from_opcode(Opcode opcode);
