#pragma once
#include "axiom/Base/BaseObject.hpp"
#include "axiom/VMContext.hpp"
#include <axiom/Process.hpp>
#include <iostream>

class PRINT : public BaseInstruction {
public:
    explicit PRINT() {};

    bool exec(Process& ctx) override {
        ObjectPtr value = ctx.vm.peek();
        std::cout << value->__debug_str__() << std::endl;
        return true;
    }

    std::string name() const override { return "PRINT"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 1; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<PRINT>();
    }
};
