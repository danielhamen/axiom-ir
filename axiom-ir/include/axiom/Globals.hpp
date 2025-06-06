#pragma once
#include "axiom/Process.hpp"
#include "Registry/ObjectRegistry.hpp"
#include "Registry/InstructionRegistry.hpp"
#include "Registry/LiteralRegistry.hpp"
#include "axiom/Base/BaseInstruction.hpp"
#include <unordered_map>

class Globals {
public:
    static Globals& instance() {
        static Globals instance;
        return instance;
    }

    ObjectRegistry objects;
    InstructionRegistry instructions;
    LiteralRegistry literals;
    std::unordered_map<int, Process> threads;

private:
    Globals() = default;
    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;
};
