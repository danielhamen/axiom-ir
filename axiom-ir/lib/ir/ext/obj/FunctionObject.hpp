#pragma once
#include "axiom/Base/BaseInstruction.hpp"
#include "axiom/Base/BaseObject.hpp"
#include "axiom/VMContext.hpp"

class FunctionObject : public BaseObject {
public:
    explicit FunctionObject();

    ObjectPtr __typename__() const override;
    ObjectPtr __call__(const std::vector<ObjectPtr>& args) override;

private:
    std::vector<std::string> param_names;
    std::vector<InstructionPtr> body;
    VMContext closure;
};
