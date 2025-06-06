#pragma once
#include "axiom/Base/BaseLiteral.hpp"
#include "axiom/is_reserved.hpp"
#include "../obj/SymbolObject.hpp"
#include <regex>

class SymbolLiteral : public BaseLiteral {
public:
    bool test(const std::string& value) const override {
        return std::regex_match(value, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$")) && !is_reserved(value);
    }

    ObjectPtr parse(const std::string& value) const override {
        return std::make_shared<SymbolObject>(value);
    }

    std::string name() const override {
        return "symbol";
    }
};
