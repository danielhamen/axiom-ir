#pragma once
#include "../core/Process.hpp"

namespace exec {
    bool ADD(Process& p);
    bool SUB(Process& p);
    bool MUL(Process& p);
    bool DIV(Process& p);
    bool MOD(Process& p);
    bool EQ(Process& p);
    bool GT(Process& p);
    bool LT(Process& p);
}
