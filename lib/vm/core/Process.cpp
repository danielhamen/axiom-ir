#pragma once
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
                std::cerr << "Error registering label" << std::endl;
                return;
            }
            pc = 0;
        }
    }

    if (!labels.exists("main")) {
        std::cerr << "Expected .main label. None found.";
        return;
    }

    pc = labels.get("main");
    while (!completed && !broken) {
        exec_step(*this);
    }
}
