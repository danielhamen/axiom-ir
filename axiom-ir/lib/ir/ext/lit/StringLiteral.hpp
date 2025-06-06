#pragma once
#include "axiom/Base/BaseLiteral.hpp"
#include "../obj/StrObject.hpp"

class StringLiteral : public BaseLiteral {
public:
    bool test(const std::string& value) const override {
        return value.size() >= 2 && (
            (value.front() == '"' && value.back() == '"') ||
            (value.front() == '\'' && value.back() == '\'')
        );
    }

    ObjectPtr parse(const std::string& value) const override {
        return std::make_shared<StrObject>(value.substr(1, value.size() - 2));
    }

    std::string name() const override {
        return "string";
    }
};
