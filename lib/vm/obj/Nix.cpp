#include "Nix.hpp"
#include <stdexcept>

std::string Nix::__str__() const {
    return "undefined";
}

bool Nix::__bool__() const {
    return false;
}

std::string Nix::__name__() const {
    return "Nix";
}

std::shared_ptr<Nix> Nix::instance() {
    static std::shared_ptr<Nix> inst = std::make_shared<Nix>();
    return inst;
}

std::shared_ptr<Object> Nix::__add__(const Object&) const {
    throw std::runtime_error("Cannot perform operations on 'undefined'");
}

std::shared_ptr<Object> Nix::__not__() const {
    throw std::runtime_error("Cannot perform operations on 'undefined'");
}
