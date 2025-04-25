#pragma once
#include <string>
#include <sstream>

struct Buffer {
    std::ostringstream out;
    void write (const std::string&);
    void dump  () const;
    void flush ();
};
