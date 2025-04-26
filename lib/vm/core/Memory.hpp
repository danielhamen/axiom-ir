#pragma once
#include <unordered_map>
#include "../obj/Object.hpp"

struct Memory {
    std::unordered_map<std::string, std::shared_ptr<Object>> mem;
    void declare(const std::string&);
    void set    (const std::string&, const std::shared_ptr<Object>&);
    void remove (const std::string&);
    bool has    (const std::string&) const;
    const std::shared_ptr<Object>& get(const std::string&) const;
};
