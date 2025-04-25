#pragma once
#include "EXIT.hpp"
#include "exec.hpp"
bool exec::EXIT(Process& p)  {
    p.completed = true;
    return true;
}
