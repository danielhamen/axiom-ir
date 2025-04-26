#include "Boolean.hpp"
#include <string>
#include "Object.hpp"

Boolean::Boolean(bool v) : value(v) {}

std::string Boolean::__str__() const {
    return value ? "true" : "false";
}

bool Boolean::__bool__() const {
    return value;
}

std::string Boolean::__name__() const {
    return "boolean";
}

std::shared_ptr<Object> Boolean::__eq__(const Object& o) const {
    return std::make_shared<Boolean>(o.__bool__() == value);
}

std::shared_ptr<Object> Boolean::__and__(const Object& o) const {
    return std::make_shared<Boolean>(value && o.__bool__());
}

std::shared_ptr<Object> Boolean::__or__(const Object& o) const {
    return std::make_shared<Boolean>(value || o.__bool__());
}

std::shared_ptr<Object> Boolean::__not__() const {
    return std::make_shared<Boolean>(!value);
}
