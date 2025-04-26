#pragma once
#include "Scalar.hpp"

class Decimal : public Scalar {
public:
    double value;
    Decimal(double v);

    std::string __str__() const override;
    bool __bool__() const override;
    std::string __name__() const override;

    std::shared_ptr<Object> __add__(const Object& o) const override;
    std::shared_ptr<Object> __sub__(const Object& o) const override;
    std::shared_ptr<Object> __mul__(const Object& o) const override;
    std::shared_ptr<Object> __div__(const Object& o) const override;

    std::shared_ptr<Object> __eq__ (const Object& o) const override;
    std::shared_ptr<Object> __lt__ (const Object& o) const override;
    std::shared_ptr<Object> __gt__ (const Object& o) const override;
    std::shared_ptr<Object> __le__ (const Object& o) const override;
    std::shared_ptr<Object> __ge__ (const Object& o) const override;
    std::shared_ptr<Object> __and__(const Object& o) const override;
    std::shared_ptr<Object> __or__ (const Object& o) const override;
    std::shared_ptr<Object> __not__() const override;
};
