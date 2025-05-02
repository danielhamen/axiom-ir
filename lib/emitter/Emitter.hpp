
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../vm/helpers/parse_raw_bytecode.hpp"
#include "../vm/helpers/str_decode.hpp"
#include "../vm/helpers/str_encode.hpp"
#include "../frontend/AST.hpp"
#include "../vm/core/Bytecode.hpp"

class Emitter {
public:
    std::vector<std::shared_ptr<ASTNode>>& program;
    Emitter(std::vector<std::shared_ptr<ASTNode>>& program);

    // Main entrypoint: emit bytecode for a full AST
    std::vector<Bytecode> emit();

private:
    std::vector<Bytecode> bytecode;
    std::vector<Bytecode> emit_node(const std::shared_ptr<ASTNode>& node);
    std::vector<Bytecode> emit_declaration(const std::shared_ptr<Declaration>& decl);
    std::vector<Bytecode> emit_expression_stmt(const std::shared_ptr<ExpressionStmt>& exprStmt);
    std::vector<Bytecode> emit_function_stmt(const std::shared_ptr<FunctionStmt>& funcStmt);
    std::vector<Bytecode> emit_assignment(const std::shared_ptr<Assignment>& assign);
    std::vector<Bytecode> emit_binary_op(const std::shared_ptr<BinaryOp>& binop);
    std::vector<Bytecode> emit_unary_op(const std::shared_ptr<UnaryOp>& unop);
    std::vector<Bytecode> emit_literal(const std::shared_ptr<Literal>& literal);
    std::vector<Bytecode> emit_variable(const std::shared_ptr<Variable>& variable);
    std::vector<Bytecode> emit_meta_stmt(const std::shared_ptr<MetaStmt>& metaStmt);
    std::vector<Bytecode> emit_call_expr(const std::shared_ptr<CallExpr>& callExpr);
    std::vector<Bytecode> emit_if_stmt(const std::shared_ptr<IfStmt>& ifStmt);
    std::vector<Bytecode> emit_return(const std::shared_ptr<ReturnStmt>& ret);
    std::vector<Bytecode> emit_namespace(const std::shared_ptr<Namespace>& ns);
    std::vector<Bytecode> emit_field_access(const std::shared_ptr<FieldAccess>& fieldAccess);
};

std::string resolve_field_access(const std::shared_ptr<ASTNode>& callee);
