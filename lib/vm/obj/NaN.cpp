#include "NaN.hpp"
#include <limits>

std::string NaN::__str__() const {
    return "NaN";
}

bool NaN::__bool__() const {
    return false;
}

double NaN::__double__() const {
    return std::numeric_limits<double>::quiet_NaN();
}

int64_t NaN::__int__() const {
    return 0;
}

std::string NaN::__name__() const {
    return "NaN";
}

std::shared_ptr<NaN> NaN::instance() {
    static std::shared_ptr<NaN> inst = std::make_shared<NaN>();
    return inst;
}
