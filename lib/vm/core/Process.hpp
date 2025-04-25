#pragma once
#include <vector>
#include "Buffer.hpp"
#include "Bytecode.hpp"
#include "OperandStack.hpp"
#include "SectionTable.hpp"
#include "LabelMap.hpp"
#include "Memory.hpp"
#include "CallStack.hpp"

struct Process {
    std::vector<Bytecode>     module               ;
    Buffer                    buffer               ;
    OperandStack              stack                ;
    SectionTable              sections             ;
    LabelMap                  labels               ;
    Memory                    memory               ;
    size_t                    pc            = 0    ;
    CallStack                 callstack            ;
    bool                      completed     = false;
    bool                      broken        = false;

    Process(std::vector<Bytecode> m) : module(std::move(m)) {};

    /**
     * Begins the process
     */
    void execute();
};
