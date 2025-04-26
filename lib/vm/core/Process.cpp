#include <iostream>
#include "Process.hpp"
#include "Bytecode.hpp"
#include "../exec/exec.hpp"
#include "../helpers/exec_step.hpp"

void Process::execute() {
    // Collect all labels
    for (size_t c = 0; c < module.size(); c++) {
        Bytecode b  = module.at(c);
        if (b.opcode == OP_LABEL) {
            pc = c;
            bool ok = exec::LABEL(*this);
            if (!ok) {
                err("Error registering label", 2);
                return;
            }
            pc = 0;
        }
    }

    if (!labels.exists("main")) {
        err("Expected .main label. None found.", 1);
        return;
    }

    pc = labels.get("main");
    while (!completed && !broken) {
        exec_step(*this);
    }
}

void Process::err(const std::string& message, const int& code) {
    std::cerr << "An error occured during the bytecode execution." << std::endl << "\tDuring process count: " << pc << std::endl << message << std::endl;
    exit(code);
}
