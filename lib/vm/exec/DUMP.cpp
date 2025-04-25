#pragma once
#include "DUMP.hpp"
#include "exec.hpp"
bool exec::DUMP(Process& p) {
    p.buffer.dump();
    return true;
}
