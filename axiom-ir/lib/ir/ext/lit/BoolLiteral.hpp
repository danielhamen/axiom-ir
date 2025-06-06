#pragma once
#include "axiom/Base/BaseLiteral.hpp"
#include "../obj/BoolObject.hpp"

class BoolLiteral : public BaseLiteral {
public:
    bool test(const std::string& value) const override {
        return value == "true" || value == "false";
    }

    ObjectPtr parse(const std::string& value) const override {
        return std::make_shared<BoolObject>(value == "true");
    }

    std::string name() const override {
        return "bool";
    }
};
