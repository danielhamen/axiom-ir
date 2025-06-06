#include "SymbolObject.hpp"
#include "StrObject.hpp"
#include "BoolObject.hpp"
#include "IntObject.hpp"
#include "FloatObject.hpp"

SymbolObject::SymbolObject(std::string name) : name(std::move(name)) {}

const std::string& SymbolObject::get_name() const {
    return name;
}

ObjectPtr SymbolObject::__typename__() const {
    return std::make_shared<StrObject>("symbol");
}

ObjectPtr SymbolObject::__str__() const {
    return std::make_shared<StrObject>(name);
}

ObjectPtr SymbolObject::__bool__() const {
    return std::make_shared<BoolObject>(true);  // Symbols are always truthy
}

ObjectPtr SymbolObject::__int__() const {
    throw std::runtime_error("Cannot cast SymbolObject to int");
}

ObjectPtr SymbolObject::__float__() const {
    throw std::runtime_error("Cannot cast SymbolObject to float");
}

bool SymbolObject::__debug_bool__() const {
    return true;
}

std::string SymbolObject::__debug_str__() const {
    return name;
}

int SymbolObject::__debug_int__() const {
    throw std::runtime_error("Cannot debug-cast SymbolObject to int");
}

double SymbolObject::__debug_float__() const {
    throw std::runtime_error("Cannot debug-cast SymbolObject to float");
}
