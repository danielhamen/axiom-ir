#pragma once
#include "FLUSH.hpp"
#include "exec.hpp"
bool exec::FLUSH(Process& p) {
    p.buffer.flush();
    return true;
}
