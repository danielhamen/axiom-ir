#pragma once
#include "axiom/Base/BaseObject.hpp"
#include "axiom/VMContext.hpp"
#include "../obj/NilObject.hpp"
#include <axiom/Process.hpp>

class PUSH_NIL : public BaseInstruction {
public:
    explicit PUSH_NIL() {};

    bool exec(Process& ctx) override {
        auto nil_obj = std::make_shared<NilObject>();
        ctx.vm.push(nil_obj);
        return true;
    }

    std::string name() const override { return "PUSH_NIL"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 0; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<PUSH_NIL>();
    }
};
