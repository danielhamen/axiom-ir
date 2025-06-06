#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Buffer.hpp"
#include "Bytecode.hpp"
#include "OperandStack.hpp"
#include "SectionTable.hpp"
#include "LabelMap.hpp"
#include "Memory.hpp"
#include "CallStack.hpp"
#include "EnvStack.hpp"

struct Process {
    std::vector<Bytecode>     module               ;
    Buffer                    buffer               ;
    OperandStack              stack                ;
    SectionTable              sections             ;
    LabelMap                  labels               ;
    Memory                    global_memory        ;
    size_t                    pc            = 0    ;
    EnvStack                  env_stack            ;
    CallStack                 callstack            ;
    bool                      completed     = false;
    bool                      broken        = false;

    Process(std::vector<Bytecode> m) : module(std::move(m)) {
        env_stack.push_scope();      // ← global-scope frame
    };

    void register_globals();

    /**
     * Begins the process
     */
    void execute();

    void err(const std::string& message, const int& code);
    void err(const std::string& message);
};
