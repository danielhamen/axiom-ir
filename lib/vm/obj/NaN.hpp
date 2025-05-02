#pragma once
#include "Object.hpp"

class NaN : public Object {
public:
    std::string __str__() const override;
    bool __bool__() const override;
    double __double__() const override;
    int64_t __int__() const override;
    std::string __name__() const override;

    static std::shared_ptr<NaN> instance();
};
