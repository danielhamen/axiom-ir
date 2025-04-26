#pragma once
#include <vector>
#include <string>
#include "../core/Bytecode.hpp"

std::vector<Bytecode> parse_raw_bytecode(const std::string &input);
