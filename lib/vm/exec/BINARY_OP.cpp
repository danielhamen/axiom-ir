#include "BINARY_OP.hpp"
#include <stdexcept>

// Define macro locally to this translation unit
#define BINARY_OP(name, method)                     \
bool exec::name(Process& p) {                       \
    if (p.stack.size() < 2)                         \
        throw std::runtime_error(#name " underflow"); \
    auto rhs = p.stack.pop();                       \
    auto lhs = p.stack.pop();                       \
    p.stack.push(lhs->method(*rhs));                \
    return true;                                    \
}

BINARY_OP(ADD,   __add__)
BINARY_OP(SUB,   __sub__)
BINARY_OP(MUL,   __mul__)
BINARY_OP(DIV,   __div__)
BINARY_OP(MOD,   __mod__)
BINARY_OP(EQ,    __eq__)
BINARY_OP(GT,    __gt__)
BINARY_OP(LT,    __lt__)
BINARY_OP(OR,    __or__)
BINARY_OP(AND,    __and__)
#undef BINARY_OP
