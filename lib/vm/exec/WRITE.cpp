#include "WRITE.hpp"
#include "exec.hpp"
bool exec::WRITE(Process& p) {
    p.buffer.write(p.stack.pop()->__str__());
    return true;
}
