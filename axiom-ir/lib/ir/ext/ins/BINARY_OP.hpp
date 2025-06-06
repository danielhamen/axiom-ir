#pragma once
#include "axiom/Base/BaseInstruction.hpp"
#include <axiom/Process.hpp>
#include <axiom/Base/BaseObject.hpp>
#include <functional>

enum BINARY_OP_TYPE {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EQ,
    LT,
    GT,
};

class BINARY_OP : public BaseInstruction {
public:
    explicit BINARY_OP(BINARY_OP_TYPE op) : op(op) {}

    bool exec(Process& ctx) override {
        ObjectPtr rhs = ctx.vm.pop();
        ObjectPtr lhs = ctx.vm.pop();

        switch (op) {
            case ADD: ctx.vm.push(lhs->__add__(rhs)); break;
            case SUB: ctx.vm.push(lhs->__sub__(rhs)); break;
            case MUL: ctx.vm.push(lhs->__mul__(rhs)); break;
            case DIV: ctx.vm.push(lhs->__div__(rhs)); break;
            case MOD: ctx.vm.push(lhs->__mod__(rhs)); break;
            case EQ:  ctx.vm.push(lhs->__eq__ (rhs)); break;
            case LT:  ctx.vm.push(lhs->__lt__ (rhs)); break;
            case GT:  ctx.vm.push(lhs->__gt__ (rhs)); break;
        }
        return true;
    }

    std::string name() const override { return "BINARY_OP"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 2; }

    static std::function<InstructionPtr(const ArgList&)> CALL_Factory(BINARY_OP_TYPE op) {
        return [op](const ArgList&) {
            return std::make_shared<BINARY_OP>(op);
        };
    }

private:
    BINARY_OP_TYPE op;
};
