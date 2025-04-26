#include "Undefined.hpp"
#include "Boolean.hpp"
#include "String.hpp"
#include <memory>

Undefined::Undefined() {}

std::string Undefined::__str__() const {
    return "undefined";
}

bool Undefined::__bool__() const {
    return false;
}

std::string Undefined::__name__() const {
    return "undefined";
}

std::shared_ptr<Object> Undefined::__add__(const Object& o) const {
    return std::make_shared<String>("undefined" + o.__str__());
}

std::shared_ptr<Object> Undefined::__eq__(const Object& o) const {
    return std::make_shared<Boolean>(false);
}
