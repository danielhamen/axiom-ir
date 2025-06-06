#include <axiom/Globals.hpp>
#include "BoolObject.hpp"
#include "FloatObject.hpp"
#include "IntObject.hpp"
#include "NilObject.hpp"
#include "__init__.hpp"

void init_obj() {
    Globals::instance().objects.register_type("int", IntObject::Factory);
    Globals::instance().objects.register_type("float", FloatObject::Factory);
    Globals::instance().objects.register_type("bool", BoolObject::Factory);
    Globals::instance().objects.register_type("nil", NilObject::Factory);
}
