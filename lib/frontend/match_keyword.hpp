#pragma once
#include <string>
#include <optional>
#include "Keyword.hpp"

std::optional<Keyword> match_keyword(const std::string& word);
