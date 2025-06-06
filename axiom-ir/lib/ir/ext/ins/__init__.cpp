#include <axiom/Globals.hpp>
#include "DECLARE.hpp"
#include "GET.hpp"
#include "BINARY_OP.hpp"
#include "PUSH.hpp"
#include "PUSH_NIL.hpp"
#include "EXIT.hpp"
#include "THREAD_START.hpp"
#include "TYPEOF.hpp"
#include "PRINT.hpp"
#include "__init__.hpp"

void init_ins() {
    Globals::instance().instructions.register_opcode("PUSH", PUSH::Factory);
    Globals::instance().instructions.register_opcode("PUSH_NIL", PUSH_NIL::Factory);
    Globals::instance().instructions.register_opcode("TYPEOF", TYPEOF::Factory);
    Globals::instance().instructions.register_opcode("EXIT", EXIT::Factory);
    Globals::instance().instructions.register_opcode("PRINT", PRINT::Factory);
    Globals::instance().instructions.register_opcode("DECLARE", DECLARE::Factory);
    Globals::instance().instructions.register_opcode("GET", GET::Factory);

    Globals::instance().instructions.register_opcode("THREAD_START", THREAD_START::Factory);

    Globals::instance().instructions.register_opcode("ADD", BINARY_OP::CALL_Factory(ADD));
    Globals::instance().instructions.register_opcode("SUB", BINARY_OP::CALL_Factory(SUB));
    Globals::instance().instructions.register_opcode("MUL", BINARY_OP::CALL_Factory(MUL));
    Globals::instance().instructions.register_opcode("DIV", BINARY_OP::CALL_Factory(DIV));
    Globals::instance().instructions.register_opcode("MOD", BINARY_OP::CALL_Factory(MOD));
    Globals::instance().instructions.register_opcode("EQ",  BINARY_OP::CALL_Factory(EQ));
    Globals::instance().instructions.register_opcode("LT",  BINARY_OP::CALL_Factory(LT));
    Globals::instance().instructions.register_opcode("GT",  BINARY_OP::CALL_Factory(GT));
}
