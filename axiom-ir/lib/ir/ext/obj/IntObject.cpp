#include "IntObject.hpp"
#include "StrObject.hpp"
#include "FloatObject.hpp"
#include "BoolObject.hpp"

IntObject::IntObject(int val) : value(val) {}

ObjectPtr IntObject::__typename__() const {
    return std::make_shared<StrObject>("int");
}

ObjectPtr IntObject::__str__() const {
    return std::make_shared<StrObject>(std::to_string(value));
}

ObjectPtr IntObject::__bool__() const {
    return std::make_shared<BoolObject>(value != 0);
}

ObjectPtr IntObject::__int__() const {
    return std::make_shared<IntObject>(value);
}

ObjectPtr IntObject::__float__() const {
    return std::make_shared<FloatObject>(static_cast<float>(value));
}

bool IntObject::__debug_bool__() const { return value != 0; }
std::string IntObject::__debug_str__() const { return std::to_string(value); }
int IntObject::__debug_int__() const { return value; }
double IntObject::__debug_float__() const { return static_cast<float>(value); }

ObjectPtr IntObject::__add__(const ObjectPtr& rhs) {
    return std::make_shared<IntObject>(value + rhs->__debug_int__());
}

ObjectPtr IntObject::__sub__(const ObjectPtr& rhs) {
    return std::make_shared<IntObject>(value - rhs->__debug_int__());
}

ObjectPtr IntObject::__mul__(const ObjectPtr& rhs) {
    return std::make_shared<IntObject>(value * rhs->__debug_int__());
}

ObjectPtr IntObject::__div__(const ObjectPtr& rhs) {
    return std::make_shared<IntObject>(value / rhs->__debug_int__());
}

ObjectPtr IntObject::__mod__(const ObjectPtr& rhs) {
    return std::make_shared<IntObject>(value % rhs->__debug_int__());
}

ObjectPtr IntObject::__eq__(const ObjectPtr& rhs) {
    return std::make_shared<BoolObject>(value == rhs->__debug_int__());
}
