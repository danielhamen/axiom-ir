#include "String.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include <memory>

String::String(const std::string& v) : value(v) {}

std::string String::__str__() const {
    return value;
}

bool String::__bool__() const {
    return !value.empty();
}

std::string String::__name__() const {
    return "string";
}

std::shared_ptr<Object> String::__add__(const Object& o) const {
    return std::make_shared<String>(value + o.__str__());
}

std::shared_ptr<Object> String::__eq__(const Object& o) const {
    const auto* p = dynamic_cast<const String*>(&o);
    if (!p) return std::make_shared<Boolean>(false);
    return std::make_shared<Boolean>(value == p->value);
}
std::shared_ptr<Object> String::__mul__(const Object& o) const {
    const auto* p = dynamic_cast<const Integer*>(&o);
    if (!p) throw std::runtime_error("TypeError: string * " + o.__name__());
    std::string out;
    for (int i = 0; i < p->value; ++i) out += value;
    return std::make_shared<String>(out);
}
