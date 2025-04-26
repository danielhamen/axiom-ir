#include "Desugarer.hpp"
#include "AST.hpp"

Desugarer::Desugarer(std::vector<std::shared_ptr<ASTNode>>& ast) : ast(ast) {};

std::vector<std::shared_ptr<ASTNode>> Desugarer::desugar() {
    std::vector<std::shared_ptr<ASTNode>> result;
    for (const auto& node : ast) {
        result.push_back(desugar_node(node));
    }
    return result;
}

std::shared_ptr<ASTNode> Desugarer::desugar_node(std::shared_ptr<ASTNode> node) {
    if (!node) return nullptr;

    switch (node->type) {
        // case ASTNodeType::DECLARATION:
        //     return desugar_declaration(std::static_pointer_cast<Declaration>(node));
        // case ASTNodeType::ASSIGNMENT:
        //     return desugar_assignment(std::static_pointer_cast<Assignment>(node));
        // case ASTNodeType::EXPRESSION_STMT:
        //     return desugar_expression_stmt(std::static_pointer_cast<ExpressionStmt>(node));
        // case ASTNodeType::IF_STMT:
        //     return desugar_if_stmt(std::static_pointer_cast<IfStmt>(node));
        case ASTNodeType::GUARD_STMT:
            return desugar_guard_stmt(std::static_pointer_cast<GuardStmt>(node));
        // case ASTNodeType::WHILE_STMT:
        //     return desugar_while_stmt(std::static_pointer_cast<WhileStmt>(node));
        // case ASTNodeType::BLOCK_STMT:
        //     return desugar_block_stmt(std::static_pointer_cast<BlockStmt>(node));
        case ASTNodeType::FUNCTION_STMT:
            return desugar_func_decl(std::static_pointer_cast<FunctionStmt>(node));
        // case ASTNodeType::RETURN_STMT:
        //     return desugar_return_stmt(std::static_pointer_cast<ReturnStmt>(node));
        // case ASTNodeType::STRUCT_DECL:
        //     return desugar_struct_decl(std::static_pointer_cast<StructDecl>(node));
        // case ASTNodeType::IMPORT_DECL:
        //     return desugar_import_decl(std::static_pointer_cast<ImportDecl>(node));
        // case ASTNodeType::CALL_EXPR:
        //     return desugar_call_expr(std::static_pointer_cast<CallExpr>(node));
        default:
            // For things like literals, variables, binary ops, just return as is
            return node;
    }
}

// --- Individual desugar methods ---

std::shared_ptr<ASTNode> Desugarer::desugar_declaration(std::shared_ptr<Declaration> decl) {
    // TODO: handle destructuring, multiple vars, chained assignment, etc.
    return decl;
}

std::shared_ptr<ASTNode> Desugarer::desugar_assignment(std::shared_ptr<Assignment> assign) {
    // TODO: handle chained assignment: x = y = z = 5;
    return assign;
}

std::shared_ptr<ASTNode> Desugarer::desugar_expression_stmt(std::shared_ptr<ExpressionStmt> expr_stmt) {
    expr_stmt->expression = desugar_node(expr_stmt->expression);
    return expr_stmt;
}

std::shared_ptr<ASTNode> Desugarer::desugar_if_stmt(std::shared_ptr<IfStmt> if_stmt) {
    // if_stmt->condition = desugar_node(if_stmt->condition);
    // if_stmt->thenBranch = desugar_node(if_stmt->thenBranch);
    // if (if_stmt->elseBranch.has_value()) {
    //     if_stmt->elseBranch = desugar_node(if_stmt->elseBranch.value());
    // }
    return if_stmt;
}

std::shared_ptr<ASTNode> Desugarer::desugar_guard_stmt(std::shared_ptr<GuardStmt> guard_stmt) {
    // Build a NOT(cond) expression
    auto not_condition = std::make_shared<UnaryOp>("!", desugar_node(guard_stmt->condition));

    auto else_branch = desugar_node(guard_stmt->elseBranch);

    return std::make_shared<IfStmt>(
        not_condition,
        else_branch
    );
}

std::shared_ptr<ASTNode> Desugarer::desugar_while_stmt(std::shared_ptr<WhileStmt> while_stmt) {
    // while_stmt->condition = desugar_node(while_stmt->condition);
    // while_stmt->body = desugar_node(while_stmt->body);
    return while_stmt;
}

std::shared_ptr<ASTNode> Desugarer::desugar_block_stmt(std::shared_ptr<BlockStmt> block_stmt) {
    // std::vector<std::shared_ptr<ASTNode>> new_statements;
    // for (auto& stmt : block_stmt->statements) {
    //     new_statements.push_back(desugar_node(stmt));
    // }
    // block_stmt->statements = std::move(new_statements);
    return block_stmt;
}

std::shared_ptr<ASTNode> Desugarer::desugar_func_decl(std::shared_ptr<FunctionStmt> func_decl) {
    for (int i = 0; i < func_decl->body.size(); i++) {
        func_decl->body.at(i) = desugar_node(func_decl->body.at(i));
    }

    return func_decl;
}

std::shared_ptr<ASTNode> Desugarer::desugar_return_stmt(std::shared_ptr<ReturnStmt> return_stmt) {
    // if (return_stmt->value.has_value()) {
    //     return_stmt->value = desugar_node(return_stmt->value.value());
    // }
    return return_stmt;
}

std::shared_ptr<ASTNode> Desugarer::desugar_struct_decl(std::shared_ptr<StructDecl> struct_decl) {
    // Usually nothing to desugar here yet
    return struct_decl;
}

std::shared_ptr<ASTNode> Desugarer::desugar_import_decl(std::shared_ptr<ImportDecl> import_decl) {
    // Nothing to desugar
    return import_decl;
}

std::shared_ptr<ASTNode> Desugarer::desugar_call_expr(std::shared_ptr<CallExpr> call_expr) {
    // call_expr->callee = desugar_node(call_expr->callee);
    // for (auto& arg : call_expr->arguments) {
    //     arg = desugar_node(arg);
    // }
    return call_expr;
}

// --- Utility ---

std::shared_ptr<BlockStmt> Desugarer::flatten(const std::vector<std::shared_ptr<ASTNode>>& stmts) {
    return std::make_shared<BlockStmt>(stmts);
}
