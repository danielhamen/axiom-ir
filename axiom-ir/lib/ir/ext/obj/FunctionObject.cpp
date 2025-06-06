#include "FunctionObject.hpp"
#include "NilObject.hpp"
#include "StrObject.hpp"
#include "axiom/Base/BaseInstruction.hpp"
#include "axiom/Process.hpp"

FunctionObject::FunctionObject() {}

ObjectPtr FunctionObject::__typename__() const {
    return std::make_shared<StrObject>("function");
}

ObjectPtr FunctionObject::__call__(const std::vector<ObjectPtr>& args) {
    VMContext local = closure;
    for (size_t i = 0; i < param_names.size(); ++i) {
        local.declare(param_names[i], args[i]);
    }

    Process p;
    p.vm = local;
    p.pt = body;
    p.pc = 0;
    p.dispatch();

    return local.stack.empty() ? std::make_shared<NilObject>() : local.pop();

}
