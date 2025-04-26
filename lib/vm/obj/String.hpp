#pragma once
#include "Object.hpp"
#include <string>

class String : public Object {
public:
    std::string value;

    String(const std::string& v);

    std::string __str__() const override;
    bool __bool__() const override;
    std::string __name__() const override;

    std::shared_ptr<Object> __add__(const Object& o) const override;
    std::shared_ptr<Object> __mul__(const Object& o) const override;
    std::shared_ptr<Object> __eq__(const Object& o) const override;
};
