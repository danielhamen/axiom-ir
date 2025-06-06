#pragma once
#include <memory>
#include <string>
#include <vector>
#include <functional>

class BaseObject;
using ObjectPtr = std::shared_ptr<BaseObject>;

struct Process;
class BaseInstruction;
using InstructionPtr = std::shared_ptr<BaseInstruction>;
using ObjectPtr = std::shared_ptr<BaseObject>;
using ArgList = std::vector<ObjectPtr>;

class BaseInstruction {
public:
    virtual ~BaseInstruction() = default;

    virtual bool exec(Process& ctx) = 0;
    virtual std::string name() const = 0;
    virtual size_t arity() const = 0;
    virtual size_t min_stack_size() const = 0;

    // Factory function signature each instruction must match
    using Factory = std::function<InstructionPtr(const ArgList&)>;
};
