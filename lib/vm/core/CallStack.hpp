#pragma once
#include <vector>

struct CallStack {
    std::vector<size_t> stack;
    void push(const size_t);
    size_t pop();
    bool   empty() const;
    size_t size() const;
    size_t back() const;
};
