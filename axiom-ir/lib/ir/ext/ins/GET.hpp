#pragma once
#include "axiom/Base/BaseObject.hpp"
#include "axiom/VMContext.hpp"
#include <axiom/Process.hpp>
#include <memory>

class GET : public BaseInstruction {
public:
    explicit GET() {};

    bool exec(Process& ctx) override {
        auto var_name = ctx.vm.pop()->__debug_str__();
        ctx.vm.push(ctx.vm.lookup(var_name));

        return true;
    }

    std::string name() const override { return "GET"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 1; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<GET>();
    }
};
