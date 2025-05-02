#include <iostream>
#include "Process.hpp"
#include "Bytecode.hpp"
#include "../exec/exec.hpp"
#include "../helpers/exec_step.hpp"

void Process::execute() {
    // Collect all labels
    for (size_t c = 0; c < module.size(); ++c) {
        const Bytecode& b = module[c];
        if (b.opcode == OP_LABEL) {
            const std::string& name = b.operand.at(0);

            // Skip label if invalid
            if (name.empty()) {
                std::cerr << "Invalid label at index " << c << std::endl;
                exit(3);
            }

            // Register the label → next instruction
            labels.set(name, c + 1);
        }
    }

    if (!labels.exists("main")) {
        err("Expected .main label. None found.");
        return;
    }

    pc = labels.get("main");
    while (!completed && !broken) {
        exec_step(*this);
    }
}

void Process::err(const std::string& message, const int& code) {
    std::cerr << "An error occured during the bytecode execution." << std::endl << "\tDuring process count: " << pc << std::endl << "Error: " << message << std::endl;
    completed = true;
    broken = true;
}

void Process::err(const std::string& message) {
    err(message, -1);
}
