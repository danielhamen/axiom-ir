#pragma once
#include "../core/Process.hpp"

namespace exec {
    // VM opcode handlers
    bool LABEL(Process&);
    bool PUSH(Process&);
    bool POP(Process&);
    bool DUP(Process&);
    bool DECL(Process&);
    bool TYPE(Process&);
    bool CAST(Process&);
    bool SWAP(Process&);
    bool SET(Process&);
    bool GET(Process&);
    bool DEL(Process&);
    bool WRITE(Process&);
    bool FLUSH(Process&);
    bool DUMP(Process&);
    bool ADD(Process&);
    bool SUB(Process&);
    bool MUL(Process&);
    bool DIV(Process&);
    bool MOD(Process&);
    bool EQ(Process&);
    bool GT(Process&);
    bool LT(Process&);
    bool OR(Process&);
    bool AND(Process&);
    bool NOT(Process&);
    bool JMP(Process&);
    bool JNZ(Process&);
    bool JZ(Process&);
    bool EXIT(Process&);
    bool RET(Process&);
    bool CALL(Process&);
    bool RAND(Process&);
    bool TIME(Process&);
    bool LIST_NEW(Process&);
    bool LIST_GET(Process&);
    bool LIST_SET(Process&);
    bool LIST_LEN(Process&);
    bool LIST_INS(Process&);
    bool ACCESS(Process&);
    bool SETFIELD(Process&);
}
