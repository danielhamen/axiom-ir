#pragma once
#include "Object.hpp"

class Nil : public Object {
public:
    std::string __str__() const override;
    bool __bool__() const override;
    std::string __name__() const override;

    // Singleton pattern
    static std::shared_ptr<Nil> instance();
};
