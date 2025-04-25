#pragma once
#include <vector>
#include "../obj/Object.hpp"

struct OperandStack {
    std::vector<std::shared_ptr<Object>> nodes;
    void push(const std::shared_ptr<Object>&);
    std::shared_ptr<Object> pop();
    bool empty() const;
    size_t size()  const;
    std::shared_ptr<Object> back() const;
};
