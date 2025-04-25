#pragma once
#include "OperandStack.hpp"

void OperandStack::push(const std::shared_ptr<Object>& v) {
    nodes.push_back(v);
}
std::shared_ptr<Object> OperandStack::pop() {
    if (nodes.empty()) throw std::runtime_error("OperandStack underflow");
    auto v = nodes.back();
    nodes.pop_back();
    return v;
}
bool OperandStack::empty() const {
    return nodes.empty();
}
size_t OperandStack::size() const {
    return nodes.size();
}
std::shared_ptr<Object> OperandStack::back() const {
    return nodes.back();
}
