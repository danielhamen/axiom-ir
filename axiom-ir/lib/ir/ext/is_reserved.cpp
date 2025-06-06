#include <axiom/is_reserved.hpp>

bool is_reserved(const std::string& symbol) {
    return (
        symbol == "true"    ||
        symbol == "false"   ||
        symbol == "nix"     ||
        symbol == "nan"     ||
        symbol == "nil"
    );
}
