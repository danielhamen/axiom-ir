#pragma once
#include "axiom/Base/BaseObject.hpp"

class BoolObject : public BaseObject {
public:
    explicit BoolObject(bool value);

    ObjectPtr __typename__() const override;
    ObjectPtr __str__() const override;
    ObjectPtr __bool__() const override;
    ObjectPtr __int__() const override;
    ObjectPtr __float__() const override;
    bool      __debug_bool__() const override;
    std::string __debug_str__() const override;
    int       __debug_int__() const override;
    double    __debug_float__() const override;

    ObjectPtr __eq__(const ObjectPtr& rhs) override;

private:
    bool value;
};
