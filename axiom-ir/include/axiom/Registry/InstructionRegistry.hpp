#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

class BaseInstruction;
class BaseObject;

using InstructionPtr = std::shared_ptr<BaseInstruction>;
using ArgList = std::vector<std::shared_ptr<BaseObject>>;

class InstructionRegistry {
public:
    using InstructionFactory = std::function<InstructionPtr(const ArgList&)>;

    void register_opcode(const std::string& name, InstructionFactory factory) {
        if (factories.contains(name)) {
            throw std::runtime_error("Instruction already registered: " + name);
        }
        factories[name] = factory;
    }

    InstructionPtr create(const std::string& name, const ArgList& args = {}) const {
        auto it = factories.find(name);
        if (it == factories.end()) {
            throw std::runtime_error("Unknown instruction: " + name);
        }
        return it->second(args);
    }

    bool has(const std::string& name) const {
        return factories.contains(name);
    }

private:
    std::unordered_map<std::string, InstructionFactory> factories;
};
