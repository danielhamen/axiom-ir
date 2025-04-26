#include "Decimal.hpp"
#include "Integer.hpp"
#include "Boolean.hpp"
#include "String.hpp"
#include <memory>

Decimal::Decimal(double v) : value(v) {}

std::string Decimal::__str__() const {
    return std::to_string(value);
}

bool Decimal::__bool__() const {
    return value != 0.0;
}

std::string Decimal::__name__() const {
    return "decimal";
}

std::shared_ptr<Object> Decimal::__add__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Decimal>(value + p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Decimal>(value + static_cast<double>(p->value));
    }
    if (const auto* p = dynamic_cast<const String*>(&o)) {
        return std::make_shared<String>(__str__() + p->value);
    }
    throw std::runtime_error("TypeError: decimal + " + o.__name__());
}

std::shared_ptr<Object> Decimal::__sub__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Decimal>(value - p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Decimal>(value - static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal - " + o.__name__());
}

std::shared_ptr<Object> Decimal::__mul__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Decimal>(value * p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Decimal>(value * static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal * " + o.__name__());
}

std::shared_ptr<Object> Decimal::__div__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        if (p->value == 0.0) throw std::runtime_error("ZeroDivisionError: decimal / decimal");
        return std::make_shared<Decimal>(value / p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        if (p->value == 0) throw std::runtime_error("ZeroDivisionError: decimal / integer");
        return std::make_shared<Decimal>(value / static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal / " + o.__name__());
}

std::shared_ptr<Object> Decimal::__eq__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value == p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value == static_cast<double>(p->value));
    }
    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> Decimal::__lt__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value < p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value < static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal < " + o.__name__());
}

std::shared_ptr<Object> Decimal::__gt__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value > p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value > static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal > " + o.__name__());
}

std::shared_ptr<Object> Decimal::__le__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value <= p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value <= static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal <= " + o.__name__());
}

std::shared_ptr<Object> Decimal::__ge__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value >= p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value >= static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: decimal >= " + o.__name__());
}


std::shared_ptr<Object> Decimal::__or__(const Object& o) const {
    return std::make_shared<Boolean>(__bool__() || o.__bool__());
}
std::shared_ptr<Object> Decimal::__and__(const Object& o) const {
    return std::make_shared<Boolean>(__bool__() && o.__bool__());
}
std::shared_ptr<Object> Decimal::__not__() const {
    return std::make_shared<Boolean>(!__bool__());
}
