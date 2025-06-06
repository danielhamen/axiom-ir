#pragma once
#include "axiom/Base/BaseObject.hpp"

class StrObject : public BaseObject {
public:
    explicit StrObject(std::string value);

    ObjectPtr __typename__() const override;
    ObjectPtr __str__() const override;
    ObjectPtr __bool__() const override;
    ObjectPtr __int__() const override;
    ObjectPtr __float__() const override;
    bool      __debug_bool__() const override;
    std::string __debug_str__() const override;
    int       __debug_int__() const override;
    double     __debug_float__() const override;

    ObjectPtr __add__(const ObjectPtr& rhs) override;
    ObjectPtr __eq__(const ObjectPtr& rhs) override;

    const std::string& value() const;

private:
    std::string val;
};
