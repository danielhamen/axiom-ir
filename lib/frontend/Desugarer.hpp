#pragma once
#include <vector>
#include <memory>
#include "AST.hpp"

// The Desugarer rewrites complex AST nodes into simpler forms
class Desugarer {
public:
    std::vector<std::shared_ptr<ASTNode>>& ast;
    Desugarer(std::vector<std::shared_ptr<ASTNode>>& ast);
    std::vector<std::shared_ptr<ASTNode>> desugar();

private:
    // Internal recursive helpers
    static std::shared_ptr<ASTNode> desugar_node(std::shared_ptr<ASTNode> node);

    static std::shared_ptr<ASTNode> desugar_declaration(std::shared_ptr<Declaration> decl);
    static std::shared_ptr<ASTNode> desugar_assignment(std::shared_ptr<Assignment> assign);
    static std::shared_ptr<ASTNode> desugar_expression_stmt(std::shared_ptr<ExpressionStmt> expr_stmt);
    static std::shared_ptr<ASTNode> desugar_if_stmt(std::shared_ptr<IfStmt> if_stmt);
    static std::shared_ptr<ASTNode> desugar_guard_stmt(std::shared_ptr<GuardStmt> guard_stmt);
    static std::shared_ptr<ASTNode> desugar_while_stmt(std::shared_ptr<WhileStmt> while_stmt);
    static std::shared_ptr<ASTNode> desugar_block_stmt(std::shared_ptr<BlockStmt> block_stmt);
    static std::shared_ptr<ASTNode> desugar_func_decl(std::shared_ptr<FunctionStmt> func_decl);
    static std::shared_ptr<ASTNode> desugar_return_stmt(std::shared_ptr<ReturnStmt> return_stmt);
    static std::shared_ptr<ASTNode> desugar_struct_decl(std::shared_ptr<StructDecl> struct_decl);
    static std::shared_ptr<ASTNode> desugar_import_decl(std::shared_ptr<ImportDecl> import_decl);
    static std::shared_ptr<ASTNode> desugar_call_expr(std::shared_ptr<CallExpr> call_expr);

    // Utility: flatten multiple statements into a block
    static std::shared_ptr<BlockStmt> flatten(const std::vector<std::shared_ptr<ASTNode>>& stmts);
};
