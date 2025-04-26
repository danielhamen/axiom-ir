#include "Scientific.hpp"
#include "Decimal.hpp"
#include "Integer.hpp"
#include "Boolean.hpp"
#include <sstream>
#include <memory>

Scientific::Scientific(double v) : value(v) {}

std::string Scientific::__str__() const {
    std::ostringstream ss;
    ss.precision(10);
    ss << std::scientific << value;
    return ss.str();
}

bool Scientific::__bool__() const {
    return value != 0.0;
}

std::string Scientific::__name__() const {
    return "scientific";
}

std::shared_ptr<Object> Scientific::__add__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Scientific>(value + p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Scientific>(value + p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Scientific>(value + static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific + " + o.__name__());
}

std::shared_ptr<Object> Scientific::__sub__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Scientific>(value - p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Scientific>(value - p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Scientific>(value - static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific - " + o.__name__());
}

std::shared_ptr<Object> Scientific::__mul__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Scientific>(value * p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Scientific>(value * p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Scientific>(value * static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific * " + o.__name__());
}

std::shared_ptr<Object> Scientific::__div__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        if (p->value == 0.0) throw std::runtime_error("ZeroDivisionError");
        return std::make_shared<Scientific>(value / p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        if (p->value == 0.0) throw std::runtime_error("ZeroDivisionError");
        return std::make_shared<Scientific>(value / p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        if (p->value == 0) throw std::runtime_error("ZeroDivisionError");
        return std::make_shared<Scientific>(value / static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific / " + o.__name__());
}

std::shared_ptr<Object> Scientific::__eq__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Boolean>(value == p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value == p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value == static_cast<double>(p->value));
    }
    return std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> Scientific::__lt__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Boolean>(value < p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value < p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value < static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific < " + o.__name__());
}

std::shared_ptr<Object> Scientific::__gt__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Boolean>(value > p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value > p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value > static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific > " + o.__name__());
}

std::shared_ptr<Object> Scientific::__le__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Boolean>(value <= p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value <= p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value <= static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific <= " + o.__name__());
}

std::shared_ptr<Object> Scientific::__ge__(const Object& o) const {
    if (const auto* p = dynamic_cast<const Scientific*>(&o)) {
        return std::make_shared<Boolean>(value >= p->value);
    }
    if (const auto* p = dynamic_cast<const Decimal*>(&o)) {
        return std::make_shared<Boolean>(value >= p->value);
    }
    if (const auto* p = dynamic_cast<const Integer*>(&o)) {
        return std::make_shared<Boolean>(value >= static_cast<double>(p->value));
    }
    throw std::runtime_error("TypeError: scientific >= " + o.__name__());
}
