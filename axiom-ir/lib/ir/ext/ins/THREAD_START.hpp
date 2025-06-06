#pragma once
#include "axiom/Base/BaseObject.hpp"
#include "axiom/Globals.hpp"
#include "axiom/VMContext.hpp"
#include <axiom/Process.hpp>

class THREAD_START : public BaseInstruction {
public:
    explicit THREAD_START() {};

    bool exec(Process& ctx) override {
        auto tid = ctx.vm.pop()->__debug_int__();
        auto has_thread = Globals::instance().threads.contains(tid);
        if (!has_thread) {
            throw std::runtime_error("Thread not found: '" + std::to_string(tid) + "'");
        }

        auto thread = Globals::instance().threads[tid];
        thread.dispatch();

        return true;
    }

    std::string name() const override { return "THREAD_START"; }
    size_t arity() const override { return 0; }
    size_t min_stack_size() const override { return 1; }

    static InstructionPtr Factory(const ArgList& args) {
        return std::make_shared<THREAD_START>();
    }
};
