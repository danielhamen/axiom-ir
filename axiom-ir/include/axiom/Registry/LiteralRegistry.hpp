#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>

#include "../Base/BaseLiteral.hpp"
#include "../Base/BaseObject.hpp"

using LiteralPtr = std::shared_ptr<BaseLiteral>;
using LiteralFactory = std::function<LiteralPtr()>;

class LiteralRegistry {
public:
    void register_literal(const std::string& name, LiteralFactory factory) {
        if (literals.contains(name)) {
            throw std::runtime_error("Literal already registered: " + name);
        }
        literals[name] = factory;
    }

    LiteralPtr get(const std::string& name) const {
        auto it = literals.find(name);
        if (it == literals.end()) {
            throw std::runtime_error("Unknown literal: " + name);
        }
        return it->second();
    }

    bool has(const std::string& name) const {
        return literals.contains(name);
    }

    // Finds the first matching literal type for a given input
    LiteralPtr find_matching(const std::string& literal) const {
        for (const auto& [name, factory] : literals) {
            auto handler = factory();
            if (handler->test(literal)) {
                return handler;
            }
        }
        throw std::runtime_error("No matching literal found for: " + literal);
    }

    // Directly parse the literal into an ObjectPtr
    ObjectPtr parse(const std::string& literal) const {
        auto handler = find_matching(literal);
        return handler->parse(literal);
    }

private:
    std::unordered_map<std::string, LiteralFactory> literals;
};
