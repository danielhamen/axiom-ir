#pragma once

enum Keyword {
    KW_LET,             // variable declaration
    KW_IF,              // if block
    KW_ELIF,            // else-if block
    KW_ELSE,            // else block
    KW_GUARD,           // guard block
    KW_WHILE,           // while loop
    KW_FOR,             // for loop
    KW_IN,              // for ... in ...
    KW_BREAK,           // break out of loop
    KW_CONTINUE,        // continue loop
    KW_RETURN,          // return from function
    KW_META,            // Meta keyword
    KW_FN,              // inline-function declaration
    KW_LAMBDA,          // lambda-function declaration
    KW_FUNC,            // function declaration
    KW_STRUCT,          // struct declaration
    KW_IMPORT,          // import modules
    KW_EXPORT,          // export functions/types
    KW_AS,              // rename imports
    KW_MATCH,           // pattern matching (like switch)
    KW_CASE,            // case branch inside match
    KW_DEFAULT,         // default branch inside match
    KW_TRUE,            // literal true
    KW_FALSE,           // literal false
    KW_NULL,            // literal null
    KW_TRY,             // try block
    KW_CATCH,           // catch block
    KW_THROW,           // throw an error
    KW_DEFER,           // run after scope exit (golang-style)
    KW_TYPE,            // user-defined type (aliasing)
};
