#include "CAST.hpp"
bool exec::CAST(Process &p) {
    // 1) Which type?  (e.g. "Integer")
    auto typeName = p.module[p.pc].operand.at(0);

    // 2) Pop the value to convert
    auto val = p.stack.pop();

    // 3) Fetch the ClassObject from global memory
    auto clsObj = p.global_memory.get(typeName);
    auto co     = std::dynamic_pointer_cast<ClassObject>(clsObj);
    if (!co) throw std::runtime_error("CAST: unknown type " + typeName);

    // 4) Push the argument back and invoke the “constructor”
    p.stack.push(val);
    co->invoke(p);

    return true;
}
