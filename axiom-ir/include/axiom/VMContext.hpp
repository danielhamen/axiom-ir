#pragma once
#include <vector>
#include <unordered_map>

class BaseObject;
using ObjectPtr = std::shared_ptr<BaseObject>;

struct Reference {
    size_t addr;
    int8_t type; // 0=let
                 // 1=fix
                 // 2=tmp
};

struct VMContext {
    std::vector<ObjectPtr> stack;
    std::unordered_map<size_t, ObjectPtr> memory;
    std::unordered_map<std::string, Reference> declarations;
    std::unordered_map<std::string, std::string> pragmas;

    size_t next_ptr = 0; // simple bump allocator

    // Stack operations
    ObjectPtr pop() {
        if (stack.empty()) throw std::runtime_error("Stack underflow");
        auto x = stack.back(); stack.pop_back();
        return x;
    }

    void push(const ObjectPtr& obj) {
        stack.push_back(obj);
    }

    ObjectPtr peek(size_t depth = 0) const {
        if (depth >= stack.size()) throw std::runtime_error("Stack underflow on peek()");
        return stack[stack.size() - 1 - depth];
    }

    // Memory allocation
    size_t alloc(const ObjectPtr& obj) {
        size_t addr = next_ptr++;
        memory[addr] = obj;
        return addr;
    }

    void set_at(size_t addr, const ObjectPtr& obj) {
        if (!memory.contains(addr)) throw std::runtime_error("Invalid memory address");
        memory[addr] = obj;
    }

    void del_at(size_t addr) {
        if (!memory.contains(addr)) throw std::runtime_error("Invalid memory address");
        memory.erase(addr);
    }

    void undeclare(std::string name) {
        if (!declarations.contains(name)) throw std::runtime_error("Invalid declarations address");
        declarations.erase(name);
    }

    ObjectPtr get_at(size_t addr) const {
        auto it = memory.find(addr);
        if (it == memory.end()) throw std::runtime_error("Invalid memory access");
        return it->second;
    }

    // Declarations (variables)
    void declare(const std::string& name, const ObjectPtr& obj, int8_t type = 0) {
        size_t addr = alloc(obj);
        declarations[name] = Reference(addr, type);
    }

    void assign(const std::string& name, const ObjectPtr& obj) {
        if (!declarations.contains(name)) throw std::runtime_error("Undeclared variable: " + name);
        auto ref = declarations[name];
        if (ref.type == 0)
            set_at(ref.addr, obj);
        if (ref.type == 1)
            throw std::runtime_error("Cannot assign to constant");
    }

    ObjectPtr lookup(const std::string& name) {
        if (!declarations.contains(name)) throw std::runtime_error("Undeclared variable: " + name);
        auto ref = declarations.at(name);
        auto value = get_at(ref.addr);

        // temperary delcaration so remove
        if (ref.type == 2) {
            del_at(ref.addr);
            undeclare(name);
        }
        return value;
    }

    // Pragmas
    void set_pragma(const std::string& key, const std::string& value) {
        pragmas[key] = value;
    }

    std::string get_pragma(const std::string& key, const std::string& fallback = "") const {
        auto it = pragmas.find(key);
        return (it != pragmas.end()) ? it->second : fallback;
    }

    bool is_pragma_enabled(const std::string& key) const {
        auto it = pragmas.find(key);
        return it != pragmas.end() && it->second == "true";
    }
};
