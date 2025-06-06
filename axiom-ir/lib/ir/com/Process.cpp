#include <iostream>
#include <thread>
#include <axiom/Process.hpp>
#include <thread>
#include "axiom/Base/BaseInstruction.hpp"

void Process::dispatch() {
    ps = ProcessStatus::RUNNING;
    while (ps == ProcessStatus::RUNNING) {
        int pc_0 = pc;
        auto ins = pt.at(pc);
        auto exp_mss = ins->min_stack_size();
        if (vm.stack.size() < exp_mss) {
            std::cerr << "StackExpectanceError: Stack was expected to have at least '" << exp_mss << "' items before executing opcode '" << ins->name() << "'" << std::endl;
            ps = ProcessStatus::ERROR;
            break;
        }

        bool ok = ins->exec(*this);
        int pc_1 = pc;

        if (ok == false) {
            ps = ProcessStatus::ERROR;
            break;
        }

        if (pc_0 == pc_1) {
            ++pc;
            continue;
        }
    }
}

void Process::kill() {
    ps = ProcessStatus::KILLED;
}

void Process::pause() {
    ps = ProcessStatus::PAUSED;
}

void Process::resume() {
    ps = ProcessStatus::RUNNING;
    Process::dispatch();
}

void Process::wait(int ms, ProcessStatus end_status) {
    ps = ProcessStatus::WAITING;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    ps = end_status;
}

void Process::wait(int ms) {
    Process::wait(ms, ProcessStatus::RUNNING);
}
