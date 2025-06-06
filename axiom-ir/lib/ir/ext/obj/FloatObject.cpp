#include "FloatObject.hpp"
#include "StrObject.hpp"
#include "IntObject.hpp"
#include "BoolObject.hpp"
#include <iomanip>
#include <ios>
#include <sstream>

FloatObject::FloatObject(double val) : value(val) {}

ObjectPtr FloatObject::__typename__() const {
    return std::make_shared<StrObject>("float");
}

ObjectPtr FloatObject::__str__() const {
    std::ostringstream ss;
    ss << value;
    return std::make_shared<StrObject>(ss.str());
}

ObjectPtr FloatObject::__bool__() const {
    return std::make_shared<BoolObject>(value != 0.0);
}

ObjectPtr FloatObject::__int__() const {
    return std::make_shared<IntObject>(static_cast<int>(value));
}

ObjectPtr FloatObject::__float__() const {
    return std::make_shared<FloatObject>(value);
}

bool FloatObject::__debug_bool__() const { return value != 0.0; }
std::string FloatObject::__debug_str__() const {
    std::ostringstream ss;
    ss << std::setprecision(17) << value;
    return ss.str();
}
int FloatObject::__debug_int__() const { return static_cast<int>(value); }
double FloatObject::__debug_float__() const { return value; }

ObjectPtr FloatObject::__add__(const ObjectPtr& rhs) {
    return std::make_shared<FloatObject>(value + rhs->__debug_float__());
}

ObjectPtr FloatObject::__sub__(const ObjectPtr& rhs) {
    return std::make_shared<FloatObject>(value - rhs->__debug_float__());
}

ObjectPtr FloatObject::__mul__(const ObjectPtr& rhs) {
    return std::make_shared<FloatObject>(value * rhs->__debug_float__());
}

ObjectPtr FloatObject::__div__(const ObjectPtr& rhs) {
    return std::make_shared<FloatObject>(value / rhs->__debug_float__());
}

ObjectPtr FloatObject::__mod__(const ObjectPtr& rhs) {
    return std::make_shared<FloatObject>(fmod(value, rhs->__debug_float__()));
}

ObjectPtr FloatObject::__eq__(const ObjectPtr& rhs) {
    return std::make_shared<BoolObject>(value == rhs->__debug_float__());
}
