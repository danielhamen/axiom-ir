#include "Nil.hpp"
#include "Nil.hpp"

std::string Nil::__str__() const {
    return "null";
}

bool Nil::__bool__() const {
    return false;
}

std::string Nil::__name__() const {
    return "Nil";
}

std::shared_ptr<Nil> Nil::instance() {
    static std::shared_ptr<Nil> inst = std::make_shared<Nil>();
    return inst;
}
