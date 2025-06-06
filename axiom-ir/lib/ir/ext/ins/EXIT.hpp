#pragma once
#include <axiom/Process.hpp>

class EXIT : public BaseInstruction {
public:
    explicit EXIT() {};

    bool exec(Process& ctx) override {
        ctx.kill();
        return true;
    }

    std::string name() const override { return "EXIT"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 0; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<EXIT>();
    }
};
