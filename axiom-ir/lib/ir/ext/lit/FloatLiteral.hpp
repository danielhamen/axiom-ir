#pragma once
#include "axiom/Base/BaseLiteral.hpp"
#include "../obj/FloatObject.hpp"
#include <regex>

class FloatLiteral : public BaseLiteral {
public:
    bool test(const std::string& value) const override {
        return std::regex_match(value, std::regex("^-?[0-9]*\\.[0-9]+$"));
    }

    ObjectPtr parse(const std::string& value) const override {
        return std::make_shared<FloatObject>(std::stof(value));
    }

    std::string name() const override {
        return "float";
    }
};
