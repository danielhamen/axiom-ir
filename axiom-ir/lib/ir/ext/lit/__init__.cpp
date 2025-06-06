#include <axiom/Globals.hpp>
#include "BoolLiteral.hpp"
#include "IntLiteral.hpp"
#include "FloatLiteral.hpp"
#include "SymbolLiteral.hpp"
#include "NilLiteral.hpp"
#include "__init__.hpp"

void init_lit() {
    Globals::instance().literals.register_literal("Int", [] { return std::make_shared<IntLiteral>(); });
    Globals::instance().literals.register_literal("Float", [] { return std::make_shared<FloatLiteral>(); });
    Globals::instance().literals.register_literal("Bool", [] { return std::make_shared<BoolLiteral>(); });
    Globals::instance().literals.register_literal("Symbol", [] { return std::make_shared<SymbolLiteral>(); });
    Globals::instance().literals.register_literal("Nil", [] { return std::make_shared<NilLiteral>(); });
}
