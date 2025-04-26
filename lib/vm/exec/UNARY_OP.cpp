#include "UNARY_OP.hpp"
#include <stdexcept>

#define UNARY_OP(name, method)                     \
bool exec::name(Process& p) {                      \
    if (p.stack.empty())                           \
        throw std::runtime_error(#name " underflow"); \
    auto val = p.stack.pop();                      \
    p.stack.push(val->method());                   \
    return true;                                   \
}

UNARY_OP(NOT, __not__)
