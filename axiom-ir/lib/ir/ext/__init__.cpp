#include "__init__.hpp"
#include "ins/__init__.hpp"
#include "lit/__init__.hpp"
#include "obj/__init__.hpp"

void init_ext() {
    init_ins();
    init_lit();
    init_obj();
}
