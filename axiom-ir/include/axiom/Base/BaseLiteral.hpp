#pragma once
#include <string>
#include <memory>

class BaseObject;
using ObjectPtr = std::shared_ptr<BaseObject>;

class BaseLiteral {
public:
    virtual ~BaseLiteral() = default;

    // Returns true if this literal handler claims the value
    virtual bool test(const std::string& value) const = 0;

    // Converts the literal into an Object (assumes test() was true)
    virtual ObjectPtr parse(const std::string& value) const = 0;

    // Optional: name of the literal (e.g., "int", "string", etc.)
    virtual std::string name() const = 0;
};
