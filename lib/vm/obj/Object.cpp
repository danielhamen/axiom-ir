#include "Object.hpp"
#include <stdexcept>

// Arithmetic & comparison
std::shared_ptr<Object> Object::__add__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for +"); }
std::shared_ptr<Object> Object::__sub__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for -"); }
std::shared_ptr<Object> Object::__mul__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for *"); }
std::shared_ptr<Object> Object::__div__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for /"); }
std::shared_ptr<Object> Object::__pow__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for **"); }
std::shared_ptr<Object> Object::__mod__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for %"); }

std::shared_ptr<Object> Object::__eq__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for =="); }
std::shared_ptr<Object> Object::__lt__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for <"); }
std::shared_ptr<Object> Object::__gt__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for >"); }
std::shared_ptr<Object> Object::__le__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for <="); }
std::shared_ptr<Object> Object::__ge__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for >="); }

std::shared_ptr<Object> Object::__and__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for &&"); }
std::shared_ptr<Object> Object::__or__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for ||"); }
std::shared_ptr<Object> Object::__not__ () const                { throw std::runtime_error("Unsupported operand type(s) for !"); }

// Numeric unary
std::shared_ptr<Object> Object::__abs__() const     { throw std::runtime_error("Unsupported operand type(s) for abs()"); }
std::shared_ptr<Object> Object::__sqrt__() const    { throw std::runtime_error("Unsupported operand type(s) for sqrt()"); }

// Logarithmic
std::shared_ptr<Object> Object::__ln__   (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for ln()"); }
std::shared_ptr<Object> Object::__log10__() const                { throw std::runtime_error("Unsupported operand type(s) for log10()"); }
std::shared_ptr<Object> Object::__log2__ () const                { throw std::runtime_error("Unsupported operand type(s) for log2()"); }
std::shared_ptr<Object> Object::__exp__  () const                { throw std::runtime_error("Unsupported operand type(s) for exp()"); }

// Trigonometric
std::shared_ptr<Object> Object::__sin__()     const { throw std::runtime_error("Unsupported operand type(s) for sin()"); }
std::shared_ptr<Object> Object::__cos__()     const { throw std::runtime_error("Unsupported operand type(s) for cos()"); }
std::shared_ptr<Object> Object::__tan__()     const { throw std::runtime_error("Unsupported operand type(s) for tan()"); }
std::shared_ptr<Object> Object::__csc__()     const { throw std::runtime_error("Unsupported operand type(s) for csc()"); }
std::shared_ptr<Object> Object::__sec__()     const { throw std::runtime_error("Unsupported operand type(s) for sec()"); }
std::shared_ptr<Object> Object::__cot__()     const { throw std::runtime_error("Unsupported operand type(s) for cot()"); }

// Inverse trig
std::shared_ptr<Object> Object::__arcsin__()  const { throw std::runtime_error("Unsupported operand type(s) for arcsin()"); }
std::shared_ptr<Object> Object::__arccos__()  const { throw std::runtime_error("Unsupported operand type(s) for arccos()"); }
std::shared_ptr<Object> Object::__arctan__()  const { throw std::runtime_error("Unsupported operand type(s) for arctan()"); }
std::shared_ptr<Object> Object::__arccsc__()  const { throw std::runtime_error("Unsupported operand type(s) for arccsc()"); }
std::shared_ptr<Object> Object::__arcsec__()  const { throw std::runtime_error("Unsupported operand type(s) for arcsec()"); }
std::shared_ptr<Object> Object::__arccot__()  const { throw std::runtime_error("Unsupported operand type(s) for arccot()"); }

// Iteration
std::shared_ptr<Object> Object::__iter__() const { throw std::runtime_error("Object is not iterable"); }
std::shared_ptr<Object> Object::__next__()       { throw std::runtime_error("Iteration not supported"); }


std::shared_ptr<Object> Object::getField(const std::string& name)  {
  return nullptr;
}
void Object::setField(const std::string& name,
                      std::shared_ptr<Object> value) {
  throw std::runtime_error(
    __name__() + " is not an instance and cannot have fields"
  );
}

bool Object::hasMethod(const std::string& /*name*/) {
    return false;
}

std::shared_ptr<Object> Object::getMethod(const std::string& /*name*/) {
    return nullptr;
}
