#pragma once
#include <string>
#include <optional>
#include "Keyword.hpp"
#include "TokenType.hpp"

struct Token {
    std::string     lexeme  ;
    size_t          idx     ; // starting index
    TokenType       type    ;
    std::optional<Keyword> keyword; // Only used if type == TOK_KEYWORD
};
