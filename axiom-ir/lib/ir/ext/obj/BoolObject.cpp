#include "BoolObject.hpp"
#include "StrObject.hpp"
#include "IntObject.hpp"
#include "FloatObject.hpp"

BoolObject::BoolObject(bool val) : value(val) {}

ObjectPtr BoolObject::__typename__() const {
    return std::make_shared<StrObject>("bool");
}

ObjectPtr BoolObject::__str__() const {
    return std::make_shared<StrObject>(value ? "true" : "false");
}

ObjectPtr BoolObject::__bool__() const {
    return std::make_shared<BoolObject>(value);
}

ObjectPtr BoolObject::__int__() const {
    return std::make_shared<IntObject>(value ? 1 : 0);
}

ObjectPtr BoolObject::__float__() const {
    return std::make_shared<FloatObject>(value ? 1.0f : 0.0f);
}

bool BoolObject::__debug_bool__() const { return value; }
std::string BoolObject::__debug_str__() const { return value ? "true" : "false"; }
int BoolObject::__debug_int__() const { return value ? 1 : 0; }
double BoolObject::__debug_float__() const { return value ? 1.0f : 0.0f; }

ObjectPtr BoolObject::__eq__(const ObjectPtr& rhs) {
    return std::make_shared<BoolObject>(value == rhs->__debug_bool__());
}
