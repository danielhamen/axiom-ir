#pragma once
#include "axiom/Base/BaseObject.hpp"
#include "axiom/VMContext.hpp"
#include <axiom/Process.hpp>

class DECLARE : public BaseInstruction {
public:
    explicit DECLARE() {};

    bool exec(Process& ctx) override {
        auto decl_type = ctx.vm.pop()->__debug_int__();
        auto decl_name = ctx.vm.pop()->__debug_str__();
        auto decl_value = ctx.vm.pop();
        ctx.vm.declare(decl_name, decl_value, decl_type);

        return true;
    }

    std::string name() const override { return "DECLARE"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 3; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<DECLARE>();
    }
};
