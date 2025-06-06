#pragma once
#include <vector>
#include "VMContext.hpp"
#include "Base/BaseInstruction.hpp"

enum ProcessStatus {
    RUNNING,
    PAUSED,
    WAITING,
    KILLED,
    INITIALIZED,
    COMPLETED,
    ERROR,
};

struct Process {
    ProcessStatus ps = INITIALIZED;   // Process status
    int pid = 0;                      // Process ID
    int pc = 0;                       // Sub-process counter
    VMContext vm;                     // Virtual machine context
    std::vector<InstructionPtr> pt;   // Process tasks

    void dispatch();
    void kill();
    void pause();
    void resume();
    void wait(int ms, ProcessStatus end_status);
    void wait(int ms);
};
