#include <string>
#include <iostream>
#include "Buffer.hpp"

void Buffer::write(const std::string& s) {
    out << s;
}
void Buffer::dump() const {
    std::cout << out.str();
}
void Buffer::flush() {
    out.str("");
    out.clear();
    std::cout << std::flush;
}
