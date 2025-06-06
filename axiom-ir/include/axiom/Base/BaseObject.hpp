#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <stdexcept>

class BaseObject;
using ObjectPtr = std::shared_ptr<BaseObject>;
using ArgList = std::vector<ObjectPtr>;

class BaseObject : public std::enable_shared_from_this<BaseObject> {
public:
    virtual ~BaseObject() = default;

    // --- Type Identification ---
    virtual ObjectPtr   __typename__()     const = 0;
    virtual ObjectPtr   __str__()          const = 0;
    virtual ObjectPtr   __bool__()         const = 0;
    virtual ObjectPtr   __int__()          const = 0;
    virtual ObjectPtr   __float__()        const = 0;
    virtual bool        __debug_bool__()   const = 0;
    virtual std::string __debug_str__()    const = 0;
    virtual int         __debug_int__()    const = 0;
    virtual double      __debug_float__()  const = 0;

    // --- Dynamic Field Access (optional for objects/instances) ---
    virtual ObjectPtr __get_attr__(const std::string& name);
    virtual void __set_attr__(const std::string& name, ObjectPtr value);

    // --- Callable interface ---
    virtual ObjectPtr __call__(const ArgList& args);

    // --- Operator overrides ---
    virtual ObjectPtr __add__(const ObjectPtr& rhs);
    virtual ObjectPtr __sub__(const ObjectPtr& rhs);
    virtual ObjectPtr __mul__(const ObjectPtr& rhs);
    virtual ObjectPtr __div__(const ObjectPtr& rhs);
    virtual ObjectPtr __mod__(const ObjectPtr& rhs);
    virtual ObjectPtr __eq__ (const ObjectPtr& rhs);
    virtual ObjectPtr __lt__ (const ObjectPtr& rhs);
    virtual ObjectPtr __gt__ (const ObjectPtr& rhs);

    static ObjectPtr Factory();

protected:
    // --- Dynamic members map ---
    std::unordered_map<std::string, ObjectPtr> dynamic_fields;
};
