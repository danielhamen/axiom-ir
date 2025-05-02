#pragma once
#include <string>

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual std::string __str__()   const = 0;
    virtual bool        __bool__()  const { return true; }
    virtual int64_t     __int__()  const { return 0; }
    virtual double      __double__()  const { return 0; }

    // arithmetic & comparison
    virtual std::shared_ptr<Object> __add__ (const Object& o) const;
    virtual std::shared_ptr<Object> __sub__ (const Object& o) const;
    virtual std::shared_ptr<Object> __mul__ (const Object& o) const;
    virtual std::shared_ptr<Object> __div__ (const Object& o) const;
    virtual std::shared_ptr<Object> __pow__ (const Object& o) const;
    virtual std::shared_ptr<Object> __abs__ () const;
    virtual std::shared_ptr<Object> __sqrt__ () const;
    virtual std::shared_ptr<Object> __mod__ (const Object& o) const;
    virtual std::shared_ptr<Object> __eq__  (const Object& o) const;
    virtual std::shared_ptr<Object> __lt__  (const Object& o) const;
    virtual std::shared_ptr<Object> __gt__  (const Object& o) const;
    virtual std::shared_ptr<Object> __le__  (const Object& o) const;
    virtual std::shared_ptr<Object> __ge__  (const Object& o) const;
    virtual std::shared_ptr<Object> __ln__  (const Object& o) const;
    virtual std::shared_ptr<Object> __log10__  () const;
    virtual std::shared_ptr<Object> __log2__  () const;
    virtual std::shared_ptr<Object> __sin__() const;
    virtual std::shared_ptr<Object> __cos__() const;
    virtual std::shared_ptr<Object> __tan__() const;
    virtual std::shared_ptr<Object> __csc__() const;
    virtual std::shared_ptr<Object> __sec__() const;
    virtual std::shared_ptr<Object> __cot__() const;
    virtual std::shared_ptr<Object> __arcsin__() const;
    virtual std::shared_ptr<Object> __arccos__() const;
    virtual std::shared_ptr<Object> __arctan__() const;
    virtual std::shared_ptr<Object> __arccsc__() const;
    virtual std::shared_ptr<Object> __arcsec__() const;
    virtual std::shared_ptr<Object> __arccot__() const;
    virtual std::shared_ptr<Object> __exp__() const;

    virtual std::shared_ptr<Object> __and__(const Object& o) const;
    virtual std::shared_ptr<Object> __or__ (const Object& o) const;
    virtual std::shared_ptr<Object> __not__() const;

    // iteration protocol
    virtual std::shared_ptr<Object> __iter__() const;
    virtual std::shared_ptr<Object> __next__();

    virtual std::string __name__() const = 0;
    virtual ~Object() = default;
};
