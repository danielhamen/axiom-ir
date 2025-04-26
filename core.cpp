// #pragma once
// #include "core.hpp"
// #include <random>
// #include <chrono>
// #include <cctype>
// #include <cstdlib>
// #include <algorithm>
// #include <iostream>
// #include <regex>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <stdexcept>
// #include <unordered_map>
// #include <functional>
// #include <memory>
// #include <limits>
// #include <iomanip>


// //------------------------------------------------------------------------------
// // Default Object implementations
// //------------------------------------------------------------------------------



//   // Decimal (floating-point)
//   class Decimal : public Scalar {
//     double value;
//   public:
//     Decimal(double v = 0.0) : value(v) {}
//     std::string __str__() const override {
//       std::ostringstream ss;
//       ss << std::setprecision(std::numeric_limits<double>::digits10) << value;
//       return ss.str();
//     }
//     bool __bool__() const override { return value != 0.0 && !std::isnan(value); }
//     std::string __name__() const override { return "Decimal"; }

//     std::shared_ptr<Object> __add__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o))
//         return std::make_shared<Decimal>(value + p->value);
//       throw std::runtime_error("TypeError: Decimal + " + o.__name__());
//     }
//     std::shared_ptr<Object> __sub__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o))
//         return std::make_shared<Decimal>(value - p->value);
//       throw std::runtime_error("TypeError: Decimal - " + o.__name__());
//     }
//     std::shared_ptr<Object> __mul__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o))
//         return std::make_shared<Decimal>(value * p->value);
//       throw std::runtime_error("TypeError: Decimal * " + o.__name__());
//     }
//     std::shared_ptr<Object> __div__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o)) {
//         if (p->value == 0.0) throw std::runtime_error("ZeroDivisionError");
//         return std::make_shared<Decimal>(value / p->value);
//       }
//       throw std::runtime_error("TypeError: Decimal / " + o.__name__());
//     }
//     std::shared_ptr<Object> __mod__(const Object& o) const override {
//       throw std::runtime_error("TypeError: % not supported on Decimal");
//     }
//     std::shared_ptr<Object> __eq__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o))
//         return std::make_shared<Bool>(value == p->value);
//       return std::make_shared<Bool>(false);
//     }
//     std::shared_ptr<Object> __lt__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o))
//         return std::make_shared<Bool>(value < p->value);
//       throw std::runtime_error("TypeError: Decimal < " + o.__name__());
//     }
//     std::shared_ptr<Object> __gt__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Decimal*>(&o))
//         return std::make_shared<Bool>(value > p->value);
//       throw std::runtime_error("TypeError: Decimal > " + o.__name__());
//     }
//   };

//   // Degree & Radian (just tagged decimals)
//   class Degree : public Decimal {
//   public:
//     using Decimal::Decimal;
//     std::string __name__() const override { return "Degree"; }
//   };
//   class Radian : public Decimal {
//   public:
//     using Decimal::Decimal;
//     std::string __name__() const override { return "Radian"; }
//   };

//   // Infinity
//   class Infinity : public Scalar {
//   public:
//     Infinity() {}
//     std::string __str__() const override { return "Infinity"; }
//     std::string __name__() const override { return "Infinity"; }
//     bool __bool__() const override { return true; }
//     // +∞ with anything → +∞; – you can refine per sign if needed
//     std::shared_ptr<Object> __add__(const Object&) const override {
//       return shared_from_this();
//     }
//     std::shared_ptr<Object> __sub__(const Object&) const override {
//       return shared_from_this();
//     }
//     std::shared_ptr<Object> __mul__(const Object&) const override {
//       return shared_from_this();
//     }
//     std::shared_ptr<Object> __div__(const Object&) const override {
//       return shared_from_this();
//     }
//   };

//   // Counter (non-negative integer, only +/++ supported)
//   class Counter : public Integer {
//   public:
//     Counter(int64_t v = 0) : Integer(v) {
//       if (v < 0) throw std::runtime_error("Counter must be ≥0");
//     }
//     std::shared_ptr<Object> __add__(const Object& o) const override {
//       auto base = Integer:: __add__(o);
//       if (auto c = std::dynamic_pointer_cast<Counter>(base))
//         return c;
//       // if result > 0, wrap as Counter
//       auto i = std::dynamic_pointer_cast<Integer>(base);
//       return std::make_shared<Counter>(std::stoll(i->__str__()));
//     }
//     std::string __name__() const override { return "Counter"; }
//   };

//   // Boolean
//   class Bool : public Object {
//     bool value;
//   public:
//     Bool(bool v) : value(v) {}
//     std::string __str__() const override { return value ? "true" : "false"; }
//     bool __bool__() const override { return value; }
//     std::string __name__() const override { return "Bool"; }
//     std::shared_ptr<Object> __eq__(const Object& o) const override {
//       if (auto p = dynamic_cast<const Bool*>(&o))
//         return std::make_shared<Bool>(value == p->value);
//       return std::make_shared<Bool>(false);
//     }
//   };

//   // Null / undefined / NaN
//   class Null : public Object {
//   public:
//     std::string __str__() const override { return "null"; }
//     bool __bool__() const override { return false; }
//     std::string __name__() const override { return "Null"; }
//   };
//   class NaN : public Object {
//   public:
//     std::string __str__() const override { return "NaN"; }
//     bool __bool__() const override { return false; }
//     std::string __name__() const override { return "NaN"; }
//   };
//   class Undefined : public Object {
//   public:
//     std::string __str__() const override { return "undefined"; }
//     bool __bool__() const override { return false; }
//     std::string __name__() const override { return "Undefined"; }
//   };

//   // String
//   class String : public Object {
//     std::string value;
//   public:
//     String(const std::string& v = "") : value(v) {}
//     std::string __str__() const override { return value; }
//     bool __bool__() const override { return !value.empty(); }
//     std::string __name__() const override { return "String"; }
//     std::shared_ptr<Object> __add__(const Object& o) const override {
//       if (auto p = dynamic_cast<const String*>(&o))
//         return std::make_shared<String>(value + p->value);
//       throw std::runtime_error("TypeError: String + " + o.__name__());
//     }
//     std::shared_ptr<Object> __eq__(const Object& o) const override {
//       if (auto p = dynamic_cast<const String*>(&o))
//         return std::make_shared<Bool>(value == p->value);
//       return std::make_shared<Bool>(false);
//     }
//   };
//   class RegEx : public String {
//   public:
//     using String::String;
//     std::string __name__() const override { return "RegEx"; }
//   };

//   // Pair (two-tuple)
//   class Pair : public Object {
//     std::shared_ptr<Object> first, second;
//   public:
//     Pair(std::shared_ptr<Object> a, std::shared_ptr<Object> b)
//       : first(std::move(a)), second(std::move(b)) {}
//     std::string __str__() const override {
//       return "(" + first->__str__() + ", " + second->__str__() + ")";
//     }
//     bool __bool__() const override { return true; }
//     std::string __name__() const override { return "Pair"; }
//   };

//   // Function
//   class Function : public Object {
//     std::function<std::shared_ptr<Object>(const std::vector<std::shared_ptr<Object>>&)> fn;
//   public:
//     Function(decltype(fn) f) : fn(std::move(f)) {}
//     std::string __str__() const override { return "<function>"; }
//     bool __bool__() const override { return true; }
//     std::string __name__() const override { return "Function"; }
//     // You’d add a CALL_METHOD or direct invocation in your VM
//   };

//   // Time / Date (simple wrappers)
//   class Time : public Object {
//     std::chrono::system_clock::time_point tp;
//   public:
//     Time() : tp(std::chrono::system_clock::now()) {}
//     std::string __str__() const override {
//       auto t = std::chrono::system_clock::to_time_t(tp);
//       std::ostringstream ss; ss << std::put_time(std::gmtime(&t), "%Y-%m-%d %H:%M:%S");
//       return ss.str();
//     }
//     std::string __name__() const override { return "Time"; }
//   };
//   class Date : public Object {
//     std::chrono::system_clock::time_point tp;
//   public:
//     Date() : tp(std::chrono::system_clock::now()) {}
//     std::string __str__() const override {
//       auto t = std::chrono::system_clock::to_time_t(tp);
//       std::ostringstream ss; ss << std::put_time(std::gmtime(&t), "%Y-%m-%d");
//       return ss.str();
//     }
//     std::string __name__() const override { return "Date"; }
//   };

//   // Iterators and Collections are left for you to flesh out:
//   class Iter : public Object {
//   public:
//     std::string __str__() const override { return "<iterator>"; }
//     std::string __name__() const override { return "Iter"; }
//     // Implement __next__() etc. if you add those virtuals
//   };

//   class Collection : public Object {
//   public:
//     std::string __str__() const override { return "<collection>"; }
//     std::string __name__() const override { return "Collection"; }
//   };
//   class Stack : public Collection {
//     // wrap a vector<shared_ptr<Object>>
//   public:
//     std::string __name__() const override { return "Stack"; }
//   };
//   class Queue : public Collection {
//     // wrap deque<shared_ptr<Object>>
//   public:
//     std::string __name__() const override { return "Queue"; }
//   };
//   class List : public Collection {
//     std::vector<std::shared_ptr<Object>> items;
//   public:
//     List(std::vector<std::shared_ptr<Object>> v = {}) : items(std::move(v)) {}
//     std::string __str__() const override {
//       std::ostringstream ss; ss << "[";
//       for (size_t i = 0; i < items.size(); ++i) {
//         ss << items[i]->__str__();
//         if (i + 1 < items.size()) ss << ", ";
//       }
//       ss << "]";
//       return ss.str();
//     }
//     std::string __name__() const override { return "List"; }
//     std::shared_ptr<Object> __iter__() const override {
//       return std::make_shared<Objects::ListIter>(items);
//     }
//   };
//   class Map : public Collection {
//     std::unordered_map<std::string, std::shared_ptr<Object>> m;
//   public:
//     std::string __str__() const override {
//       std::ostringstream ss; ss << "{";
//       bool first = true;
//       for (auto& [k,v]: m) {
//         if (!first) ss << ", ";
//         ss << k << ": " << v->__str__();
//         first = false;
//       }
//       ss << "}";
//       return ss.str();
//     }
//     std::string __name__() const override { return "Map"; }
//   };
//   class Tuple : public Collection {
//     std::vector<std::shared_ptr<Object>> items;
//   public:
//     Tuple(std::vector<std::shared_ptr<Object>> v) : items(std::move(v)) {}
//     std::string __str__() const override {
//       std::ostringstream ss; ss << "(";
//       for (size_t i = 0; i < items.size(); ++i) {
//         ss << items[i]->__str__();
//         if (i + 1 < items.size()) ss << ", ";
//       }
//       ss << ")";
//       return ss.str();
//     }
//     std::string __name__() const override { return "Tuple"; }
//   };
//   class Set : public Collection {
//     std::unordered_map<std::string, std::shared_ptr<Object>> contents;
//   public:
//     std::string __str__() const override {
//       std::ostringstream ss; ss << "{";
//       bool first = true;
//       for (auto& [k,_]: contents) {
//         if (!first) ss << ", ";
//         ss << k;
//         first = false;
//       }
//       ss << "}";
//       return ss.str();
//     }
//     std::string __name__() const override { return "Set"; }
//   };

//     class Error     : public Object {};
//     class File      : public Object {};
//     class XMLTree   : public Collection {};
//     class XMLNode   : public Collection {};

//     class String    : public Object {};
//     class RegEx     : public String {};

//     class Bool      : public Object {};

//     class Null      : public Object {};
//     class NaN       : public Object {};
//     class Undefined : public Object {};
// };
