#include "CallStack.hpp"

void CallStack::push(const size_t v) {
    stack.push_back(v);
}
size_t CallStack::pop() {
    if (stack.empty()) throw std::runtime_error("CallStack underflow");
    auto v = stack.back();
    stack.pop_back();
    return v;
}
bool CallStack::empty() const {
    return stack.empty();
}
size_t CallStack::size() const {
    return stack.size();
}
size_t CallStack::back() const {
    return stack.back();
}
