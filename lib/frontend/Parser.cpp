#include <iostream>
#include "Parser.hpp"
#include "AST.hpp"
#include "TokenType.hpp"
#include <memory>
#include <optional>
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {}

std::vector<std::shared_ptr<ASTNode>> Parser::parse() {
    std::vector<std::shared_ptr<ASTNode>> statements;
    while (!at_end()) {
        statements.push_back(parse_statement());
    }
    return statements;
}

bool Parser::at_end() const {
    return peek().type == TOK_EOF;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

const Token& Parser::advance() {
    if (!at_end()) current++;
    return previous();
}

bool Parser::check(TokenType type) const {
    if (at_end()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (auto t : types) {
        if (check(t)) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& error_message) {
    if (check(type)) return advance();
    throw std::runtime_error(error_message);
}

void Parser::synchronize() {
    while (!at_end() && peek().type != TOK_SEMICOLON) {
        advance();
    }
    if (check(TOK_SEMICOLON)) advance();
}

std::shared_ptr<BlockStmt> Parser::parse_block() {
    consume(TOK_LBRACE, "Expected '{' in parse_block");
    std::vector<std::shared_ptr<ASTNode>> stmts;
    while (!check(TOK_RBRACE) && !at_end()) {
        stmts.push_back(parse_statement());
    }
    consume(TOK_RBRACE, "Expected '}' in parse_block");
    return std::make_shared<BlockStmt>(std::move(stmts));
}

std::vector<Token> Parser::collect_until_keyword_or(TokenType stop, const std::string& keyword) {
    std::vector<Token> out;
    int brace_depth = 0;
    int paren_depth = 0;
    while (!at_end()) {
        if (peek().type == TOK_LBRACE) brace_depth++;
        else if (peek().type == TOK_RBRACE) brace_depth--;
        else if (peek().type == TOK_LPAREN) paren_depth++;
        else if (peek().type == TOK_RPAREN) paren_depth--;
        if (brace_depth == 0 && paren_depth == 0 && peek().type == stop && peek().lexeme == keyword) {
            break;
        }
        out.push_back(advance());
    }
    return out;
}

std::shared_ptr<ASTNode> Parser::parse_head(const std::vector<Token>& head_tokens) {
    Parser sub(head_tokens);
    return sub.parse_expression();
}

std::shared_ptr<ASTNode> Parser::parse_statement() {
    if (match({TOK_LBRACE})) {
        return parse_block_no_open(); // parse block statement
    }

    if (check(TOK_KEYWORD)) {
        auto kw = peek().keyword.value();
        if (kw == Keyword::KW_LET) return parse_let();
        if (kw == Keyword::KW_GUARD) return parse_guard();
        if (kw == Keyword::KW_RETURN) return parse_return();
        if (kw == Keyword::KW_META) return parse_meta();
        if (kw == Keyword::KW_FUNC) return parse_function();
        if (kw == Keyword::KW_NAMESPACE) return parse_namespace();
    }

    // assignment
    if (check(TOK_IDENTIFIER) && tokens[current + 1].type == TOK_ASSIGN) {
        Token name = advance();
        advance();
        auto value = parse_expression();
        consume(TOK_SEMICOLON, "Expected ';' in assignment");
        return std::make_shared<Assignment>(name.lexeme, value);
    }

    // call
    if (check(TOK_IDENTIFIER) && tokens[current + 1].type == TOK_LPAREN) {
        Token callee_name = advance(); // consume identifier
        auto iden = std::make_shared<Variable>(callee_name.lexeme);
        auto call = parse_call(iden);
        auto call_expr = std::dynamic_pointer_cast<CallExpr>(call);
        consume(TOK_SEMICOLON, "Expected ';' in call");
        return call_expr;
    }

    auto expr = parse_expression();
    consume(TOK_SEMICOLON, "Expected ';' in expression");
    return std::make_shared<ExpressionStmt>(expr);
}

std::shared_ptr<ASTNode> Parser::parse_let() {
    consume(TOK_KEYWORD, "Expected 'let'");

    std::shared_ptr<ASTNode> pattern;

    // Handle destructuring patterns: {x, y} or [x, y]
    if (match({TOK_LBRACE})) {
        std::vector<std::string> names;
        do {
            Token name = consume(TOK_IDENTIFIER, "Expected identifier in destructuring");
            names.push_back(name.lexeme);
        } while (match({TOK_COMMA}));
        consume(TOK_RBRACE, "Expected '}' after destructuring pattern");

        pattern = std::make_shared<DestructurePattern>(names, /* isArray = */ false);
    } else if (match({TOK_LBRACKET})) {
        std::vector<std::string> names;
        do {
            Token name = consume(TOK_IDENTIFIER, "Expected identifier in destructuring");
            names.push_back(name.lexeme);
        } while (match({TOK_COMMA}));
        consume(TOK_RBRACKET, "Expected ']' after destructuring pattern");

        pattern = std::make_shared<DestructurePattern>(names, /* isArray = */ true);
    } else if (match({TOK_LPAREN})) {
        // Optional: support tuple grouping
        std::vector<std::string> names;
        do {
            Token name = consume(TOK_IDENTIFIER, "Expected identifier in tuple pattern");
            names.push_back(name.lexeme);
        } while (match({TOK_COMMA}));
        consume(TOK_RPAREN, "Expected ')' after tuple pattern");

        pattern = std::make_shared<TuplePattern>(names);
    } else {
        // Normal single-variable declaration
        Token name = consume(TOK_IDENTIFIER, "Expected identifier after 'let'");
        pattern = std::make_shared<VariablePattern>(name.lexeme);
    }

    // Optional type annotation
    std::optional<std::string> type_annotation;
    if (match({TOK_COLON})) {
        Token typeName = consume(TOK_IDENTIFIER, "Expected type name after ':'");
        type_annotation = typeName.lexeme;
    }

    // Optional initializer
    std::optional<std::shared_ptr<ASTNode>> initializer;
    if (match({TOK_ASSIGN})) {
        initializer = parse_expression();
    }

    consume(TOK_SEMICOLON, "Expected ';' after variable declaration");

    return std::make_shared<Declaration>(pattern, type_annotation, initializer);
}

std::shared_ptr<ASTNode> Parser::parse_function() {
    consume(TOK_KEYWORD, "Expected 'func' keyword.");

    auto name = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected function name.").lexeme);

    consume(TOK_LPAREN, "Expected '(' after function name.");

    std::vector<std::pair<std::shared_ptr<ASTNode>, std::shared_ptr<ASTNode>>> params;

    if (!check(TOK_RPAREN)) {
        do {
            auto paramName = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected parameter name.").lexeme);
            consume(TOK_COLON, "Expected ':' after parameter name.");
            auto paramType = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected parameter type.").lexeme);

            params.emplace_back(paramName, paramType);
        } while (match({TOK_COMMA}));
    }

    consume(TOK_RPAREN, "Expected ')' after parameters.");

    std::optional<std::shared_ptr<ASTNode>> returnType = std::nullopt;
    if (match({TOK_COLON})) {
        auto returnTypeNode = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected return type.").lexeme);
        returnType = returnTypeNode;
    }

    if (!check(TOK_LBRACE)) throw std::runtime_error("Expected '{' before function body.");

    auto block = parse_block();

    return std::make_shared<FunctionStmt>(
        std::move(name),
        std::move(params),
        std::move(returnType),
        std::move(block->statements)
    );

}

std::shared_ptr<ASTNode> Parser::parse_namespace() {
    consume(TOK_KEYWORD, "Expected 'namespace' keyword.");

    auto name = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected namespace name.").lexeme);

    if (!check(TOK_LBRACE)) throw std::runtime_error("Expected '{' after namespace name.");

    auto block = parse_block();

    return std::make_shared<Namespace>(
        std::move(name),
        std::move(block->statements)
    );

}

std::shared_ptr<ASTNode> Parser::parse_guard() {
    consume(TOK_KEYWORD, "Expected 'guard'");
    auto condition = parse_expression();
    Token e = consume(TOK_KEYWORD, "Expected 'else'");
    if (e.lexeme != "else") throw std::runtime_error("Expected 'else'");

    std::shared_ptr<ASTNode> else_branch;

    if (check(TOK_LBRACE)) {
        else_branch = parse_block();
        match({TOK_SEMICOLON});
    } else {
        auto ex = parse_expression();
        else_branch = std::make_shared<ReturnStmt>(ex);
        consume(TOK_SEMICOLON, "Expected ';' in guard");
    }

    return std::make_shared<GuardStmt>(condition, else_branch);
}

std::shared_ptr<BlockStmt> Parser::parse_block_no_open() {
    // DO NOT consume '{' — it was already matched before calling this function
    std::vector<std::shared_ptr<ASTNode>> stmts;
    while (!check(TOK_RBRACE) && !at_end()) {
        stmts.push_back(parse_statement());
    }
    consume(TOK_RBRACE, "Expected '}'");
    return std::make_shared<BlockStmt>(std::move(stmts));
}

// Assumes '{' has already been consumed
std::shared_ptr<BlockStmt> Parser::parse_block_already_open() {
    std::vector<std::shared_ptr<ASTNode>> stmts;
    while (!check(TOK_RBRACE) && !at_end()) {
        stmts.push_back(parse_statement());
    }
    consume(TOK_RBRACE, "Expected '}'");
    return std::make_shared<BlockStmt>(std::move(stmts));
}

std::shared_ptr<ASTNode> Parser::parse_return() {
    consume(TOK_KEYWORD, "Expected 'return'");
    std::optional<std::shared_ptr<ASTNode>> value;
    if (!check(TOK_SEMICOLON)) {
        value = parse_expression();
    }
    consume(TOK_SEMICOLON, "Expected ';' after return");
    return std::make_shared<ReturnStmt>(value);
}

std::shared_ptr<ASTNode> Parser::parse_meta() {
    auto ns = std::make_shared<Variable>(consume(TOK_KEYWORD, "Expected 'Meta'.").lexeme);
    consume(TOK_DOT, "Expected '.' after 'Meta' keyword.");

    auto accessor = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected identifier.").lexeme);

    auto a_ns = std::static_pointer_cast<ASTNode>(ns);
    auto a_accessor = std::static_pointer_cast<ASTNode>(accessor);

    if (check(TOK_LPAREN)) {
        auto call = parse_call(accessor); // returns shared_ptr<ASTNode>
        consume(TOK_SEMICOLON, "Expected ';' in meta");

        // Downcast to CallExpr
        auto call_expr = std::dynamic_pointer_cast<CallExpr>(call);
        if (!call_expr) {
            throw std::runtime_error("Expected function call after Meta accessor.");
        }

        return std::make_shared<MetaStmt>(
            a_ns,
            a_accessor,
            call_expr->arguments
        );
    } else if (check(TOK_SEMICOLON)) {
        consume(TOK_SEMICOLON, "Expected ';' in meta(2)");

        return std::make_shared<MetaStmt>(
            a_ns,
            a_accessor
        );
    } else {
        throw std::runtime_error("Unexpected token after 'Meta' accessor: '" + peek().lexeme + "'");
    }
}

std::shared_ptr<ASTNode> Parser::parse_expression() {
    return parse_assignment();
}


std::shared_ptr<ASTNode> Parser::parse_assignment() {
    auto node = parse_or();

    if (match({TOK_ASSIGN})) {
        Token equals = previous();
        auto value = parse_assignment(); // right-associative!

        if (auto var = std::dynamic_pointer_cast<Variable>(node)) {
            return std::make_shared<Assignment>(var->name, value);
        } else {
            throw std::runtime_error("Invalid assignment target");
        }
    }

    return node;
}

std::shared_ptr<ASTNode> Parser::parse_or() {
    auto node = parse_and();
    while (match({TOK_OR})) {
        Token op = previous();
        auto right = parse_and();
        node = std::make_shared<BinaryOp>(op.lexeme, node, right);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_and() {
    auto node = parse_equality();
    while (match({TOK_AND})) {
        Token op = previous();
        auto right = parse_equality();
        node = std::make_shared<BinaryOp>(op.lexeme, node, right);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_equality() {
    auto node = parse_comparison();
    while (match({TOK_EQUAL, TOK_NOT_EQUAL})) {
        Token op = previous();
        auto right = parse_comparison();
        node = std::make_shared<BinaryOp>(op.lexeme, node, right);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_comparison() {
    auto node = parse_term();
    while (match({TOK_LESS, TOK_LESS_EQUAL, TOK_GREATER, TOK_GREATER_EQUAL})) {
        Token op = previous();
        auto right = parse_term();
        node = std::make_shared<BinaryOp>(op.lexeme, node, right);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_term() {
    auto node = parse_factor();
    while (match({TOK_PLUS, TOK_MINUS})) {
        Token op = previous();
        auto right = parse_factor();
        node = std::make_shared<BinaryOp>(op.lexeme, node, right);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_factor() {
    auto node = parse_unary();
    while (match({TOK_ASTERISK, TOK_SLASH, TOK_PERCENT})) {
        Token op = previous();
        auto right = parse_unary();
        node = std::make_shared<BinaryOp>(op.lexeme, node, right);
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::parse_unary() {
    if (match({TOK_MINUS, TOK_NOT})) {
        Token op = previous();
        auto operand = parse_unary();
        return std::make_shared<UnaryOp>(op.lexeme, operand);
    }
    return parse_primary();
}

std::shared_ptr<ASTNode> Parser::parse_primary() {
    if (match({TOK_INTEGER, TOK_DECIMAL, TOK_STRING})) {
        return std::make_shared<Literal>(previous().lexeme);
    }
    if (match({TOK_KEYWORD})) {
        auto kw = previous().keyword.value();
        if (kw == Keyword::KW_TRUE || kw == Keyword::KW_FALSE || kw == Keyword::KW_NULL) {
            return std::make_shared<Literal>(previous().lexeme);
        }

        if (kw == Keyword::KW_META) {
            // Special handling for Meta
            auto meta_ns = std::make_shared<Variable>("Meta");
            consume(TOK_DOT, "Expected '.' after 'Meta'");
            auto accessor = std::make_shared<Variable>(consume(TOK_IDENTIFIER, "Expected Meta accessor").lexeme);

            // If it's a function call (Meta.Time()), parse call
            if (check(TOK_LPAREN)) {
                auto call = parse_call(accessor);
                auto call_expr = std::dynamic_pointer_cast<CallExpr>(call);
                if (!call_expr) throw std::runtime_error("Expected function call after Meta accessor.");

                return std::make_shared<MetaStmt>(
                    std::static_pointer_cast<ASTNode>(meta_ns),
                    std::static_pointer_cast<ASTNode>(accessor),
                    call_expr->arguments
                );
            }
            // If just property access (Meta.Something)
            else {
                return std::make_shared<MetaStmt>(
                    std::static_pointer_cast<ASTNode>(meta_ns),
                    std::static_pointer_cast<ASTNode>(accessor)
                );
            }
        }
        throw std::runtime_error("Unexpected keyword '" + previous().lexeme + "'");
    }
    if (match({TOK_IDENTIFIER})) {
        std::shared_ptr<ASTNode> expr = std::make_shared<Variable>(previous().lexeme);

        while (match({TOK_DOT})) {
            Token name = consume(TOK_IDENTIFIER, "Expected property name after '.'");
            expr = std::make_shared<FieldAccess>(expr, std::make_shared<Variable>(name.lexeme));
        }

        if (check(TOK_LPAREN)) {
            expr = parse_call(expr);
        }

        return expr;
    }
    if (match({TOK_LPAREN})) {
        auto expr = parse_expression();
        consume(TOK_RPAREN, "Expected ')'");
        return expr;
    }
    throw std::runtime_error("Unexpected token: " + peek().lexeme);
}


std::shared_ptr<ASTNode> Parser::parse_call(std::shared_ptr<ASTNode> callee) {
    consume(TOK_LPAREN, "Expected '(' after function name");

    std::vector<std::shared_ptr<ASTNode>> arguments;

    if (!check(TOK_RPAREN)) {
        do {
            arguments.push_back(parse_expression());
        } while (match({TOK_COMMA}));
    }

    consume(TOK_RPAREN, "Expected ')' after arguments");

    return std::make_shared<CallExpr>(callee, arguments);
}
