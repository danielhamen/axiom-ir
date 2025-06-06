#pragma once
#include "axiom/Base/BaseLiteral.hpp"
#include "../obj/NilObject.hpp"

class NilLiteral : public BaseLiteral {
public:
    bool test(const std::string& value) const override {
        return value == "nil";
    }

    ObjectPtr parse(const std::string& value) const override {
        return std::make_shared<NilObject>();
    }

    std::string name() const override {
        return "nil";
    }
};
