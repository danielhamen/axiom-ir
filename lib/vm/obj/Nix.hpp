#pragma once
#include "Object.hpp"

class Nix : public Object {
public:
    std::string __str__() const override;
    bool __bool__() const override;
    std::string __name__() const override;

    // Prevent any operation on undefined
    std::shared_ptr<Object> __add__(const Object&) const override;
    std::shared_ptr<Object> __not__() const override;

    static std::shared_ptr<Nix> instance();
};
