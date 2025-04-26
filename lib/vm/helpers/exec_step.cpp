#include <iomanip>
#include <iostream>
#include "../helpers/exec_step.hpp"
#include "../core/Process.hpp"
#include "../core/Bytecode.hpp"
#include "../exec/exec.hpp"

void exec_step(Process& p) {
    Bytecode& instr = p.module.at(p.pc);
    bool ok = false;
    size_t before = p.pc;
    // std::cout << "Executing process id: '" << std::setw(5) << std::setfill('0') << p.pc << "'; bytecode: '" + instr.toString() + "'" << std::endl;
    switch (instr.opcode) {
        case OP_PUSH:  ok = exec::PUSH  (p);    break;
        case OP_POP:   ok = exec::POP   (p);    break;
        case OP_DUP:   ok = exec::DUP   (p);    break;
        case OP_DECL:  ok = exec::DECL  (p);    break;
        case OP_SWAP:  ok = exec::SWAP  (p);    break;
        case OP_SET:   ok = exec::SET   (p);    break;
        case OP_GET:   ok = exec::GET   (p);    break;
        case OP_DEL:   ok = exec::DEL   (p);    break;
        case OP_WRITE: ok = exec::WRITE (p);    break;
        case OP_FLUSH: ok = exec::FLUSH (p);    break;
        case OP_DUMP:  ok = exec::DUMP  (p);    break;
        case OP_ADD:   ok = exec::ADD   (p);    break;
        case OP_SUB:   ok = exec::SUB   (p);    break;
        case OP_MUL:   ok = exec::MUL   (p);    break;
        case OP_DIV:   ok = exec::DIV   (p);    break;
        case OP_MOD:   ok = exec::MOD   (p);    break;
        case OP_EQ:    ok = exec::EQ    (p);    break;
        case OP_GT:    ok = exec::GT    (p);    break;
        case OP_LT:    ok = exec::LT    (p);    break;
        case OP_AND:   ok = exec::AND   (p);    break;
        case OP_OR:    ok = exec::OR    (p);    break;
        case OP_NOT:   ok = exec::NOT   (p);    break;
        case OP_JMP:   ok = exec::JMP   (p);    break;
        case OP_JNZ:   ok = exec::JNZ   (p);    break;
        case OP_JZ:    ok = exec::JZ    (p);    break;
        case OP_EXIT:  ok = exec::EXIT  (p);    break;
        case OP_RET:   ok = exec::RET   (p);    break;
        case OP_CALL:  ok = exec::CALL  (p);    break;
        case OP_RAND:  ok = exec::RAND  (p);    break;
        case OP_TIME:  ok = exec::TIME  (p);    break;
        case NOP:                               break;
        case OP_LABEL: ok = true;               break;
        case OP_TYPE:  ok = exec::TYPE  (p);    break;
        case OP_CAST:  ok = exec::CAST  (p);    break;
        case OP_IN:
        case OP_SLEEP:
        case OP_FREAD:
        case OP_FWRITE:
        case OP_END:                            break;
        default:
            throw std::runtime_error("Opcode not implemented");
    }
    if (!ok) {
        p.broken = true;
        p.err("Exited with an error", 3);
    }

    if (p.pc == before && !p.completed && !p.broken) {
        p.pc++;
    }
}
