#include "axiom/Base/BaseObject.hpp"
#include <stdexcept>

ObjectPtr BaseObject::__get_attr__(const std::string& name) {
    auto it = dynamic_fields.find(name);
    if (it != dynamic_fields.end()) {
        return it->second;
    }
    throw std::runtime_error("Attribute not found: " + name);
}

void BaseObject::__set_attr__(const std::string& name, ObjectPtr value) {
    dynamic_fields[name] = value;
}

ObjectPtr BaseObject::__call__(const ArgList& args) {
    throw std::runtime_error("Object is not callable");
}

ObjectPtr BaseObject::__add__(const ObjectPtr& rhs) {
    throw std::runtime_error("Addition not supported for this object");
}

ObjectPtr BaseObject::__sub__(const ObjectPtr& rhs) {
    throw std::runtime_error("Subtraction not supported for this object");
}

ObjectPtr BaseObject::__mul__(const ObjectPtr& rhs) {
    throw std::runtime_error("Multiplication not supported for this object");
}

ObjectPtr BaseObject::__div__(const ObjectPtr& rhs) {
    throw std::runtime_error("Division not supported for this object");
}

ObjectPtr BaseObject::__mod__(const ObjectPtr& rhs) {
    throw std::runtime_error("Modulo not supported for this object");
}

ObjectPtr BaseObject::__eq__(const ObjectPtr& rhs) {
    throw std::runtime_error("Equality not supported for this object");
}

ObjectPtr BaseObject::__lt__(const ObjectPtr& rhs) {
    throw std::runtime_error("Less than not supported for this object");
}

ObjectPtr BaseObject::__gt__(const ObjectPtr& rhs) {
    throw std::runtime_error("Greater than not supported for this object");
}

ObjectPtr BaseObject::Factory() {
    throw std::runtime_error("Cannot instantiate abstract BaseObject directly");
}
