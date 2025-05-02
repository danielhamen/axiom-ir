#pragma once
#include <vector>
#include <optional>
#include <memory>
#include "Token.hpp"
#include "TokenType.hpp"
#include "Keyword.hpp"
#include "AST.hpp" // (you'll define the ASTNode, Assignment, BinaryOp, etc.)

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    std::vector<std::shared_ptr<ASTNode>> parse();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    // Core helpers
    bool at_end() const;
    const Token& advance();
    const Token& peek() const;
    const Token& previous() const;
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type) const;
    std::vector<Token> collect_until_keyword_or(TokenType stop, const std::string& keyword);
    std::shared_ptr<ASTNode> parse_head(const std::vector<Token>& head_tokens);
    std::shared_ptr<BlockStmt> parse_block();
    std::shared_ptr<ASTNode> parse_call(std::shared_ptr<ASTNode> callee);

    void synchronize(); // error recovery (optional later)

    // Parsing functions
    std::shared_ptr<ASTNode> parse_statement();
    std::shared_ptr<ASTNode> parse_expression();
    std::shared_ptr<ASTNode> parse_assignment();
    std::shared_ptr<ASTNode> parse_term();
    std::shared_ptr<ASTNode> parse_factor();
    std::shared_ptr<ASTNode> parse_primary();
    std::shared_ptr<ASTNode> parse_or();
    std::shared_ptr<ASTNode> parse_and();
    std::shared_ptr<ASTNode> parse_equality();
    std::shared_ptr<ASTNode> parse_comparison();
    std::shared_ptr<ASTNode> parse_unary();

    // Specific statement parsers
    std::shared_ptr<ASTNode> parse_let();
    std::shared_ptr<ASTNode> parse_for();
    std::shared_ptr<ASTNode> parse_return();
    std::shared_ptr<ASTNode> parse_meta();
    std::shared_ptr<ASTNode> parse_guard();
    std::shared_ptr<ASTNode> parse_function();
    std::shared_ptr<ASTNode> parse_namespace();

    // Utilities
    std::shared_ptr<BlockStmt> parse_block_already_open();
    std::shared_ptr<BlockStmt> parse_block_no_open();
    Token consume(TokenType type, const std::string& error_message);
};
