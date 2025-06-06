#pragma once
#include "axiom/Base/BaseLiteral.hpp"
#include "../obj/IntObject.hpp"
#include <regex>

class IntLiteral : public BaseLiteral {
public:
    bool test(const std::string& value) const override {
        return std::regex_match(value, std::regex("^-?[0-9]+$"));
    }

    ObjectPtr parse(const std::string& value) const override {
        return std::make_shared<IntObject>(std::stoi(value));
    }

    std::string name() const override {
        return "int";
    }
};
