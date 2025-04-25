#pragma once
#include <fstream>
#include <string>
#include "core.hpp"

int main() {
    std::string filepath = "test.axb";
    std::ifstream File(filepath);
    std::string raw_code;
    while (!File.eof()) {
        std::string line;
        std::getline(File, line);
        raw_code += line + "\n";
    }

    std::vector<Bytecode> module = parse_raw_bytecode(raw_code);
    Process proc(module);
    proc.execute();
    return 0;
}
