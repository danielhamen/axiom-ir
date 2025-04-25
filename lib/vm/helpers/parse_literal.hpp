#pragma once
#include <string>
#include "../obj/Object.hpp"

std::shared_ptr<Object> parse_literal(const std::string& tok);
