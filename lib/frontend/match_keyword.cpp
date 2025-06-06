#include "match_keyword.hpp"
std::optional<Keyword> match_keyword(const std::string& word) {
    if (word == "let")          return KW_LET;
    if (word == "if")           return KW_IF;
    if (word == "elif")         return KW_ELIF;
    if (word == "else")         return KW_ELSE;
    if (word == "while")        return KW_WHILE;
    if (word == "Meta")         return KW_META;
    if (word == "guard")        return KW_GUARD;
    if (word == "for")          return KW_FOR;
    if (word == "in")           return KW_IN;
    if (word == "break")        return KW_BREAK;
    if (word == "continue")     return KW_CONTINUE;
    if (word == "return")       return KW_RETURN;
    if (word == "func")         return KW_FUNC;
    if (word == "fn")           return KW_FN;
    if (word == "lambda")       return KW_LAMBDA;
    if (word == "struct")       return KW_STRUCT;
    if (word == "import")       return KW_IMPORT;
    if (word == "export")       return KW_EXPORT;
    if (word == "as")           return KW_AS;
    if (word == "match")        return KW_MATCH;
    if (word == "case")         return KW_CASE;
    if (word == "default")      return KW_DEFAULT;
    if (word == "true")         return KW_TRUE;
    if (word == "false")        return KW_FALSE;
    if (word == "nil")          return KW_NIL;
    if (word == "nix")          return KW_NIX;
    if (word == "nan")          return KW_NAN;
    if (word == "namespace")    return KW_NAMESPACE;
    return std::nullopt;
}
