#pragma once
#include "axiom/Base/BaseObject.hpp"
#include "axiom/VMContext.hpp"
#include <axiom/Process.hpp>
#include <memory>

class TYPEOF : public BaseInstruction {
public:
    explicit TYPEOF() {};

    bool exec(Process& ctx) override {
        auto x = ctx.vm.peek();
        auto value = x->__typename__();
        ctx.vm.push(value);
        return true;
    }

    std::string name() const override { return "TYPEOF"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 1; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<TYPEOF>();
    }

private:
    ObjectPtr value;
};
