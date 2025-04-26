#include <iostream>
#include "parse_raw_bytecode.hpp"
#include <vector>
#include <string>
#include <sstream>
#include "../core/Bytecode.hpp"
#include "../core/opmap.hpp"
#include "trim.hpp"
#include "split.hpp"

std::vector<Bytecode> parse_raw_bytecode(const std::string &input) {
    std::vector<Bytecode> code;
    std::istringstream lines(input);
    std::string line;

    while (std::getline(lines, line)) {
        // remove comments
        line = trim(line);
        if (line.empty())
            continue;

        // function label
        if (line[0] == '.') {
            code.push_back({ OP_LABEL, { line } });
            continue;
        }

        // (OPCODE,arg1,arg2…)
        if (line.front() == '(' && line.back() == ')') {
            auto inner = line.substr(1, line.size()-2);
            auto parts = split(inner, ',');
            auto it = opmap.find(parts[0]);
            if (it == opmap.end())
                throw std::runtime_error("Unknown opcode: " + parts[0]);
            Opcode opc = it->second;
            std::vector<std::string> args(parts.begin()+1, parts.end());
            code.push_back({ opc, args });
            continue;
        }

        throw std::runtime_error("Invalid line in bytecode: " + line);
    }

    return code;
}
