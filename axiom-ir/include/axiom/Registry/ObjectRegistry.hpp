#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>

class BaseObject;
using ObjectPtr = std::shared_ptr<BaseObject>;
using ObjectFactory = std::function<ObjectPtr()>;

// Simple object registry: maps type names to constructor functions
class ObjectRegistry {
public:
    void register_type(const std::string& name, ObjectFactory factory) {
        if (types.contains(name)) {
            throw std::runtime_error("Object type already registered: " + name);
        }
        types[name] = factory;
    }

    ObjectPtr create(const std::string& name) const {
        auto it = types.find(name);
        if (it == types.end()) {
            throw std::runtime_error("Unknown object type: " + name);
        }
        return it->second();
    }

    bool has(const std::string& name) const {
        return types.contains(name);
    }

private:
    std::unordered_map<std::string, ObjectFactory> types;
};
