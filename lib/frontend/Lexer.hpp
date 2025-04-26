#pragma once
#include <string>
#include <vector>
#include "Keyword.hpp"
#include "match_keyword.hpp"
#include "Token.hpp"

class Lexer {
public:
    explicit Lexer(const std::string& src);

    std::vector<Token> tokenize();

private:
    const std::string& source;
    size_t current = 0;
    size_t start   = 0;
    size_t length  = 0;

    std::vector<Token> tokens;

    // --- Core advancing functions
    bool at_end() const;
    char advance();
    char peek() const;
    char peek_next() const;
    bool match(char expected);

    // --- Token creation
    void add_token(TokenType type);
    void add_token(TokenType type, const std::string& text);
    void add_keyword_or_identifier();

    // --- Handlers
    void scan_token();
    void string();
    void number();
    void identifier();
};
