#pragma once
#include <axiom/Process.hpp>

class PUSH : public BaseInstruction {
public:
    explicit PUSH(ObjectPtr value) : value(std::move(value)) {};

    bool exec(Process& ctx) override {
        ctx.vm.push(value);
        return true;
    }

    std::string name() const override { return "PUSH"; }
    size_t arity() const override { return 1; }
    size_t min_stack_size() const override { return 0; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<PUSH>(args[0]);
    }

private:
    ObjectPtr value;
};
