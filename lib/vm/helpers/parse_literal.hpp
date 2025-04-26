#pragma once
#include <string>
#include <cctype>
#include <set>
#include <stdexcept>
#include <memory>
#include "../obj/Object.hpp"
#include "../obj/Boolean.hpp"
#include "../obj/String.hpp"
#include "../obj/Integer.hpp"
#include "../obj/Decimal.hpp"
#include "../obj/Scientific.hpp"
#include "../obj/RegEx.hpp"
#include "../helpers/str_decode.hpp"

std::shared_ptr<Object> parse_literal(const std::string& tok);
