#include "Object.hpp"
#include <stdexcept>

std::shared_ptr<Object> Object::__add__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for +"); }
std::shared_ptr<Object> Object::__sub__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for -"); }
std::shared_ptr<Object> Object::__mul__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for *"); }
std::shared_ptr<Object> Object::__div__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for /"); }
std::shared_ptr<Object> Object::__mod__ (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for %"); }
std::shared_ptr<Object> Object::__eq__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for =="); }
std::shared_ptr<Object> Object::__lt__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for <"); }
std::shared_ptr<Object> Object::__gt__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for >"); }
std::shared_ptr<Object> Object::__le__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for <="); }
std::shared_ptr<Object> Object::__ge__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for >="); }
std::shared_ptr<Object> Object::__or__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for ||"); }
std::shared_ptr<Object> Object::__and__  (const Object& o) const { throw std::runtime_error("Unsupported operand type(s) for &&"); }
std::shared_ptr<Object> Object::__not__  () const { throw std::runtime_error("Unsupported operand type(s) for !"); }

std::shared_ptr<Object> Object::__iter__() const { throw std::runtime_error("Object is not iterable"); }
std::shared_ptr<Object> Object::__next__()       { throw std::runtime_error("Iteration not supported"); }
