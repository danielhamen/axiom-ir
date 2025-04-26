#pragma once

#include <random>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <memory>
#include <limits>
#include <iomanip>

/// forward‐decl
struct Process;



///------------------------------------------------------------------------------
/// Object model
///------------------------------------------------------------------------------




class Decimal : public Scalar {
    double value;
public:
    Decimal(double v = 0.0);
};

class Degree : public Decimal {
public:
    using Decimal::Decimal;
};

class Radian : public Decimal {
public:
    using Decimal::Decimal;
};

class Infinity : public Scalar {};
class Counter  : public Scalar {};

class Bool      : public Object {};
class String    : public Object {};
class RegEx     : public String {};
class Null      : public Object {};
class NaN       : public Object {};
class Undefined : public Object {};

//–– Collections & iterators
class Iter       : public Object {};
class Collection : public Object {};
class Stack      : public Collection {};
class Queue      : public Collection {};
class List       : public Collection {};
class ListIter   : public Iter {};       // iterator for List
class Map        : public Collection {};
class Tuple      : public Collection {};
class Set        : public Collection {};

//–– Other core types
class Pair     : public Object {};
class Function : public Object {};
class Time     : public Object {};
class Date     : public Object {};


std::string               trim(const std::string&);
std::vector<std::string>  split(const std::string&, char);
bool                       is_valid_identifier(const std::string&);
std::shared_ptr<Object>    parse_literal(const std::string&);


struct SectionTable {
    std::unordered_map<std::string, size_t> sections;
};

struct LabelMap {
    std::unordered_map<std::string, size_t> labels;
    void set   (const std::string&, size_t);
    bool exists(const std::string&) const;
    size_t get (const std::string&) const;
};

/// The Process encapsulates a single module execution.
struct Process {
    std::vector<Bytecode> module;
    Buffer                buffer;
    OperandStack          stack;
    SectionTable          sections;
    LabelMap              labels;
    Memory                memory;
    size_t                pc        = 0;
    CallStack             callstack;
    bool                  completed = false;
    bool                  broken    = false;

    Process(std::vector<Bytecode>);

    void execute();
};

/// VM runner
void exec_bytecode(Process&);
std::vector<Bytecode> parse_raw_bytecode(const std::string &input);
