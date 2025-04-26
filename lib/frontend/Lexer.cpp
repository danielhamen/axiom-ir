// lexer.cpp
#include "Lexer.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "match_keyword.hpp"

#include <cctype>
#include <optional>

Lexer::Lexer(const std::string& src)
    : source(src), current(0), start(0), length(src.size())
{}

std::vector<Token> Lexer::tokenize() {
    tokens.clear();
    while (!at_end()) {
        start = current;
        scan_token();
    }
    // EOF token
    tokens.push_back(Token{"", current, TOK_EOF, std::nullopt});
    return tokens;
}

bool Lexer::at_end() const {
    return current >= length;
}

char Lexer::advance() {
    return source[current++];
}

char Lexer::peek() const {
    return at_end() ? '\0' : source[current];
}

char Lexer::peek_next() const {
    return (current + 1 >= length) ? '\0' : source[current + 1];
}

bool Lexer::match(char expected) {
    if (at_end() || source[current] != expected) return false;
    current++;
    return true;
}

void Lexer::add_token(TokenType type) {
    add_token(type, source.substr(start, current - start));
}

void Lexer::add_token(TokenType type, const std::string& text) {
    tokens.push_back(Token{text, start, type, std::nullopt});
}

void Lexer::add_keyword_or_identifier() {
    std::string text = source.substr(start, current - start);
    if (auto kw = match_keyword(text)) {
        tokens.push_back(Token{text, start, TOK_KEYWORD, *kw});
    } else {
        tokens.push_back(Token{text, start, TOK_IDENTIFIER, std::nullopt});
    }
}

void Lexer::scan_token() {
    char c = advance();
    switch (c) {
        // Single-character tokens
        case '+': add_token(TOK_PLUS);        break;
        case '-': add_token(TOK_MINUS);       break;
        case '*': add_token(TOK_ASTERISK);    break;
        case '/':
            if (match('/')) {
                // skip comment until end of line
                while (peek() != '\n' && !at_end()) advance();
            } else {
                add_token(TOK_SLASH);
            }
            break;
        case '%': add_token(TOK_PERCENT);     break;
        case '(': add_token(TOK_LPAREN);      break;
        case ')': add_token(TOK_RPAREN);      break;
        case '[': add_token(TOK_LBRACKET);      break;
        case ']': add_token(TOK_RBRACKET);      break;
        case '{': add_token(TOK_LBRACE);      break;
        case '}': add_token(TOK_RBRACE);      break;
        case ',': add_token(TOK_COMMA);       break;
        case '.': add_token(TOK_DOT);         break;
        case ';': add_token(TOK_SEMICOLON);   break;
        case ':': add_token(TOK_COLON);   break;

        // One or two character tokens
        case '=': add_token(match('=') ? TOK_EQUAL         : TOK_ASSIGN);       break;
        case '!': add_token(match('=') ? TOK_NOT_EQUAL     : TOK_NOT);          break;
        case '<': add_token(match('=') ? TOK_LESS_EQUAL    : TOK_LESS);         break;
        case '>': add_token(match('=') ? TOK_GREATER_EQUAL : TOK_GREATER);      break;
        case '&': add_token(match('&') ? TOK_AND           : TOK_UNKNOWN);      break;
        case '|': add_token(match('|') ? TOK_OR            : TOK_UNKNOWN);      break;

        // Whitespace
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            break; // skip

        // String literals
        case '"': string();  break;

        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c) || c == '_') {
                identifier();
            } else {
                add_token(TOK_UNKNOWN);
            }
    }
}

void Lexer::string() {
    // consume until closing quote
    while (peek() != '"' && !at_end()) {
        if (peek() == '\\' && peek_next() != '\0') {
            // skip escape sequence
            advance();
        }
        advance();
    }

    if (at_end()) {
        // Unterminated string; still emit what we have
        add_token(TOK_STRING);
        return;
    }

    // closing "
    advance();
    add_token(TOK_STRING, source.substr(start, current - start));
}

void Lexer::number() {
    // integer part
    while (std::isdigit(peek())) advance();

    // fractional part
    if (peek() == '.' && std::isdigit(peek_next())) {
        advance(); // consume '.'
        while (std::isdigit(peek())) advance();
        add_token(TOK_DECIMAL);
    } else {
        add_token(TOK_INTEGER);
    }
}

void Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') {
        advance();
    }
    add_keyword_or_identifier();
}
