#include "StrObject.hpp"
#include "IntObject.hpp"
#include "FloatObject.hpp"
#include "BoolObject.hpp"

StrObject::StrObject(std::string v) : val(std::move(v)) {}

ObjectPtr StrObject::__typename__() const {
    return std::make_shared<StrObject>("str");
}

ObjectPtr StrObject::__str__() const {
    return std::make_shared<StrObject>(val);
}

ObjectPtr StrObject::__bool__() const {
    return std::make_shared<BoolObject>(!val.empty());
}

ObjectPtr StrObject::__int__() const {
    try {
        return std::make_shared<IntObject>(std::stoi(val));
    } catch (...) {
        return std::make_shared<IntObject>(0);
    }
}

ObjectPtr StrObject::__float__() const {
    try {
        return std::make_shared<FloatObject>(std::stof(val));
    } catch (...) {
        return std::make_shared<FloatObject>(0.0);
    }
}

bool StrObject::__debug_bool__() const {
    return !val.empty();
}

std::string StrObject::__debug_str__() const {
    return val;
}

int StrObject::__debug_int__() const {
    try {
        return std::stoi(val);
    } catch (...) {
        return 0;
    }
}

double StrObject::__debug_float__() const {
    try {
        return std::stof(val);
    } catch (...) {
        return 0.0;
    }
}

ObjectPtr StrObject::__add__(const ObjectPtr& rhs) {
    return std::make_shared<StrObject>(val + rhs->__debug_str__());
}

ObjectPtr StrObject::__eq__(const ObjectPtr& rhs) {
    return std::make_shared<BoolObject>(val == rhs->__debug_str__());
}

const std::string& StrObject::value() const {
    return val;
}
