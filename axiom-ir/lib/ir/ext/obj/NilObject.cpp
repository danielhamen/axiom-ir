#include "IntObject.hpp"
#include "StrObject.hpp"
#include "FloatObject.hpp"
#include "BoolObject.hpp"
#include "NilObject.hpp"

NilObject::NilObject() {}

ObjectPtr NilObject::__typename__() const {
    return std::make_shared<StrObject>("nil");
}

ObjectPtr NilObject::__str__() const {
    return std::make_shared<StrObject>("nil");
}

ObjectPtr NilObject::__bool__() const {
    return std::make_shared<BoolObject>(false);
}

ObjectPtr NilObject::__int__() const {
    return std::make_shared<IntObject>(0);
}

ObjectPtr NilObject::__float__() const {
    return std::make_shared<FloatObject>(0);
}

bool NilObject::__debug_bool__() const { return false; }
std::string NilObject::__debug_str__() const { return "nil"; }
int NilObject::__debug_int__() const { return 0; }
double NilObject::__debug_float__() const { return static_cast<double>(0); }

ObjectPtr NilObject::__eq__(const ObjectPtr& rhs) {
    bool is_nil = std::dynamic_pointer_cast<NilObject>(rhs) != nullptr;
    return std::make_shared<BoolObject>(is_nil);
}
