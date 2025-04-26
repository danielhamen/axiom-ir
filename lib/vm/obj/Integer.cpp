#include "Integer.hpp"
#include "Decimal.hpp"
#include "Boolean.hpp"
#include "String.hpp"
#include <memory>

Integer::Integer(int64_t v) : value(v) {}

std::string Integer::__str__() const {
    return std::to_string(value);
}

bool Integer::__bool__() const {
    return value != 0;
}

std::string Integer::__name__() const {
    return "integer";
}

std::shared_ptr<Object> Integer::__add__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Integer>(value + p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Decimal>(static_cast<double>(value) + p->value);
    }
    if (const auto* p = dynamic_cast<const String*>(&o)) {
        return std::make_shared<String>(__str__() + p->value);
    }
    throw std::runtime_error("TypeError: integer + " + o.__name__());
}

std::shared_ptr<Object> Integer::__sub__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Integer>(value - p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Decimal>(static_cast<double>(value) - p->value);
    }
    throw std::runtime_error("TypeError: integer - " + o.__name__());
}

std::shared_ptr<Object> Integer::__mul__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Integer>(value * p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Decimal>(static_cast<double>(value) * p->value);
    }
    throw std::runtime_error("TypeError: integer * " + o.__name__());
}

std::shared_ptr<Object> Integer::__div__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        if (p->value == 0) throw std::runtime_error("ZeroDivisionError: integer / integer");
        return std::make_shared<Integer>(value / p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        if (p->value == 0.0) throw std::runtime_error("ZeroDivisionError: integer / decimal");
        return std::make_shared<Decimal>(static_cast<double>(value) / p->value);
    }
    throw std::runtime_error("TypeError: integer / " + o.__name__());
}

std::shared_ptr<Object> Integer::__mod__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        if (p->value == 0) throw std::runtime_error("ZeroDivisionError: integer % integer");
        return std::make_shared<Integer>(value % p->value);
    }
    throw std::runtime_error("TypeError: integer % " + o.__name__());
}

std::shared_ptr<Object> Integer::__eq__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value == p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(static_cast<double>(value) == p->value);
    }
    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> Integer::__lt__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value < p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(static_cast<double>(value) < p->value);
    }
    throw std::runtime_error("TypeError: integer < " + o.__name__());
}

std::shared_ptr<Object> Integer::__gt__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value > p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(static_cast<double>(value) > p->value);
    }
    throw std::runtime_error("TypeError: integer > " + o.__name__());
}

std::shared_ptr<Object> Integer::__le__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value <= p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(static_cast<double>(value) <= p->value);
    }
    throw std::runtime_error("TypeError: integer <= " + o.__name__());
}

std::shared_ptr<Object> Integer::__ge__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value >= p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(static_cast<double>(value) >= p->value);
    }
    throw std::runtime_error("TypeError: integer >= " + o.__name__());
}
std::shared_ptr<Object> Integer::__or__(const Object& o) const {
    return std::make_shared<Boolean>(__bool__() || o.__bool__());
}
std::shared_ptr<Object> Integer::__and__(const Object& o) const {
    return std::make_shared<Boolean>(__bool__() && o.__bool__());
}
std::shared_ptr<Object> Integer::__not__() const {
    return std::make_shared<Boolean>(!__bool__());
}
