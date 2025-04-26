#pragma once

enum TokenType {
    // --- Literals
    TOK_INTEGER,     // 123
    TOK_DECIMAL,     // 3.14
    TOK_STRING,      // "hello"

    // --- Identifiers / Keywords
    TOK_IDENTIFIER,  // x, foo, myVar
    TOK_KEYWORD,     // let, if, else, return,

    // --- Operators
    TOK_PLUS,        // +
    TOK_MINUS,       // -
    TOK_ASTERISK,    // *
    TOK_SLASH,       // /
    TOK_PERCENT,     // %

    TOK_EQUAL,       // ==
    TOK_NOT_EQUAL,   // !=
    TOK_LESS,        // <
    TOK_LESS_EQUAL,  // <=
    TOK_GREATER,     // >
    TOK_GREATER_EQUAL, // >=

    TOK_ASSIGN,      // =

    TOK_AND,         // &&
    TOK_OR,          // ||
    TOK_NOT,         // !

    // --- Symbols
    TOK_LPAREN,      // (
    TOK_RPAREN,      // )
    TOK_LBRACKET,    // [
    TOK_RBRACKET,    // ]
    TOK_LBRACE,      // {
    TOK_RBRACE,      // }
    TOK_COMMA,       // ,
    TOK_DOT,         // .
    TOK_COLON,       // :
    TOK_SEMICOLON,   // ;

    // --- Special
    TOK_EOF,         // End of file/input
    TOK_UNKNOWN      // Invalid/unknown character
};
