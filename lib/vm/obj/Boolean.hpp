#pragma once
#include "Object.hpp"

class Boolean : public Object {
public:
    bool value;
    Boolean(bool v);

    std::string __str__() const override;
    bool __bool__() const override;
    std::string __name__() const override;

    std::shared_ptr<Object> __eq__ (const Object& o) const override;
    std::shared_ptr<Object> __and__ (const Object& o) const override;
    std::shared_ptr<Object> __or__ (const Object& o) const override;
    std::shared_ptr<Object> __not__ () const override;
};
