#include "../helpers/get_nanotime.hpp"
#include "../obj/Integer.hpp"
#include "exec.hpp"
bool exec::TIME(Process& p) {
    p.stack.push(std::make_shared<Integer>(get_nanotime()));
    return true;
}
