#include "AST.hpp"
#include <string>

// --- ASTNode Destructor ---
ASTNode::~ASTNode() {}

// --- Literal Constructor ---
Literal::Literal(const std::string& val) : value(val) {
    type = ASTNodeType::LITERAL;
}
bool Literal::is_str() {
    return value.starts_with('"') && value.ends_with('"');
}
bool Literal::is_dec() {
    throw "not impl.";
}
bool Literal::is_int() {
    throw "not impl.";
}

// --- Variable Constructor ---
Variable::Variable(const std::string& n) : name(n) {
    type = ASTNodeType::VARIABLE;
}

// --- Namespace Reference Node ---
Namespace::Namespace(const std::shared_ptr<ASTNode> n, std::vector<std::shared_ptr<ASTNode>> body)
    : name(n), body(std::move(body)) {
    type = ASTNodeType::NAMESPACE_DECL;
}

// --- BinaryOp Constructor ---
BinaryOp::BinaryOp(const std::string& oper, std::shared_ptr<ASTNode> lhs, std::shared_ptr<ASTNode> rhs)
    : op(oper), left(std::move(lhs)), right(std::move(rhs)) {
    type = ASTNodeType::BINARY_OP;
}

// --- UnaryOp Constructor ---
UnaryOp::UnaryOp(const std::string& oper, std::shared_ptr<ASTNode> opd)
    : op(oper), operand(std::move(opd)) {
    type = ASTNodeType::UNARY_OP;
}

// --- Declaration Constructor ---
Declaration::Declaration(std::shared_ptr<ASTNode> pat,
                         std::optional<std::string> typeAnn,
                         std::optional<std::shared_ptr<ASTNode>> init)
    : pattern(std::move(pat)),
      type_annotation(std::move(typeAnn)),
      initializer(std::move(init)) {
    type = ASTNodeType::DECLARATION;
}

// --- Field Access Constructor ---
FieldAccess::FieldAccess(std::shared_ptr<ASTNode> object, std::shared_ptr<ASTNode> field)
    : object(std::move(object)), field(std::move(field)) {
    type = ASTNodeType::FIELD_ACCESS;
}

// --- VariablePattern Constructor ---
VariablePattern::VariablePattern(const std::string& n)
    : name(n) {
    type = ASTNodeType::VARIABLE_PATTERN;
}

// --- TuplePattern Constructor ---
TuplePattern::TuplePattern(std::vector<std::string> n)
    : names(std::move(n)) {
    type = ASTNodeType::TUPLE_PATTERN;
}

// --- DestructurePattern Constructor ---
DestructurePattern::DestructurePattern(std::vector<std::string> n, bool isArr)
    : names(std::move(n)), isArray(isArr) {
    type = ASTNodeType::DESTRUCTURE_PATTERN;
}

// --- Assignment Constructor ---
Assignment::Assignment(const std::string& n, std::shared_ptr<ASTNode> val)
    : name(n), value(std::move(val)) {
    type = ASTNodeType::ASSIGNMENT;
}

// --- ExpressionStmt Constructor ---
ExpressionStmt::ExpressionStmt(std::shared_ptr<ASTNode> expr) : expression(std::move(expr)) {
    type = ASTNodeType::EXPRESSION_STMT;
}

// --- MetaStmt Constructor ---
MetaStmt::MetaStmt(
    std::shared_ptr<ASTNode> ns,
    std::shared_ptr<ASTNode> call,
    std::optional<std::vector<std::shared_ptr<ASTNode>>> arg
)
    : ns(std::move(ns)), call(std::move(call)), arg(std::move(arg)) {
    type = ASTNodeType::META_STMT;
}

MetaStmt::MetaStmt(
    std::shared_ptr<ASTNode> ns,
    std::shared_ptr<ASTNode> call
)
    : ns(std::move(ns)), call(std::move(call)) {
    type = ASTNodeType::META_STMT;
}

// --- IfStmt Constructor ---
IfStmt::IfStmt(std::shared_ptr<ASTNode> cond, std::shared_ptr<ASTNode> thenB, std::vector<std::shared_ptr<ASTNode>> elifB, std::optional<std::shared_ptr<ASTNode>> elseB)
    : condition(std::move(cond)), thenBranch(std::move(thenB)), elifBranches(elifB), elseBranch(std::move(elseB)) {
    type = ASTNodeType::IF_STMT;
}

// --- GuardStmt Constructor ---
GuardStmt::GuardStmt(std::shared_ptr<ASTNode> cond, std::shared_ptr<ASTNode> elseB)
    : condition(std::move(cond)), elseBranch(std::move(elseB)) {
    type = ASTNodeType::GUARD_STMT;
}

// --- WhileStmt Constructor ---
WhileStmt::WhileStmt(std::shared_ptr<ASTNode> cond, std::shared_ptr<ASTNode> b)
    : condition(std::move(cond)), body(std::move(b)) {
    type = ASTNodeType::WHILE_STMT;
}

// --- ForInStmt Constructor ---
ForInStmt::ForInStmt(const std::string& n, std::shared_ptr<ASTNode> iter, std::shared_ptr<ASTNode> b)
    : varName(n), iterable(std::move(iter)), body(std::move(b)) {
    type = ASTNodeType::FOR_IN_STMT;
}

// --- BlockStmt Constructor ---
BlockStmt::BlockStmt(std::vector<std::shared_ptr<ASTNode>> stmts) : statements(std::move(stmts)) {
    type = ASTNodeType::BLOCK_STMT;
}

// --- FuncDecl Constructor ---
FunctionStmt::FunctionStmt(
    std::shared_ptr<ASTNode> name,
    std::vector<std::pair<std::shared_ptr<ASTNode>, std::shared_ptr<ASTNode>>> params,
    std::optional<std::shared_ptr<ASTNode>> returnType,
    std::vector<std::shared_ptr<ASTNode>> body
)
: name(name), params(params), returnType(returnType), body(body)
{
    type = ASTNodeType::FUNCTION_STMT;
}

// --- CallExpr Constructor ---
CallExpr::CallExpr(std::shared_ptr<ASTNode> c, std::vector<std::shared_ptr<ASTNode>> args)
    : callee(std::move(c)), arguments(std::move(args)) {
    type = ASTNodeType::CALL_EXPR;
}

// --- ReturnStmt Constructor ---
ReturnStmt::ReturnStmt(std::optional<std::shared_ptr<ASTNode>> v) : value(std::move(v)) {
    type = ASTNodeType::RETURN_STMT;
}

// --- StructDecl Constructor ---
StructDecl::StructDecl(const std::string& n, std::vector<std::string> f)
    : name(n), fields(std::move(f)) {
    type = ASTNodeType::STRUCT_DECL;
}

// --- ImportDecl Constructor ---
ImportDecl::ImportDecl(const std::string& m, std::optional<std::string> a)
    : module(m), alias(std::move(a)) {
    type = ASTNodeType::IMPORT_DECL;
}

std::string ast_to_string(const std::shared_ptr<ASTNode>& node) {
    if (!node) return "<null>";

    switch (node->type) {
        case ASTNodeType::LITERAL:
            return "Literal(" + static_cast<Literal*>(node.get())->value + ")";
        case ASTNodeType::VARIABLE:
            return "Variable(" + static_cast<Variable*>(node.get())->name + ")";
        case ASTNodeType::BINARY_OP: {
            auto bin = static_cast<BinaryOp*>(node.get());
            return "BinaryOp(" + bin->op + ", " + ast_to_string(bin->left) + ", " + ast_to_string(bin->right) + ")";
        }
        case ASTNodeType::UNARY_OP: {
            auto un = static_cast<UnaryOp*>(node.get());
            return "UnaryOp(" + un->op + ", " + ast_to_string(un->operand) + ")";
        }
        case ASTNodeType::DECLARATION: {
            auto decl = static_cast<Declaration*>(node.get());
            std::string out = "Declaration(";
            out += ast_to_string(decl->pattern);
            if (decl->type_annotation) {
                out += ": " + decl->type_annotation.value();
            }
            if (decl->initializer) {
                out += " = " + ast_to_string(decl->initializer.value());
            }
            out += ")";
            return out;
        }
        case ASTNodeType::VARIABLE_PATTERN: {
            auto p = static_cast<VariablePattern*>(node.get());
            return "VariablePattern(" + p->name + ")";
        }
        case ASTNodeType::TUPLE_PATTERN: {
            auto p = static_cast<TuplePattern*>(node.get());
            std::string result = "TuplePattern(";
            for (size_t i = 0; i < p->names.size(); ++i) {
                result += p->names[i];
                if (i + 1 < p->names.size()) result += ", ";
            }
            result += ")";
            return result;
        }
        case ASTNodeType::DESTRUCTURE_PATTERN: {
            auto p = static_cast<DestructurePattern*>(node.get());
            std::string result = (p->isArray ? "ArrayDestructure(" : "ObjectDestructure(");
            for (size_t i = 0; i < p->names.size(); ++i) {
                result += p->names[i];
                if (i + 1 < p->names.size()) result += ", ";
            }
            result += ")";
            return result;
        }
        case ASTNodeType::ASSIGNMENT: {
            auto assign = static_cast<Assignment*>(node.get());
            return "Assignment(" + assign->name + ", " + ast_to_string(assign->value) + ")";
        }
        case ASTNodeType::EXPRESSION_STMT: {
            auto expr = static_cast<ExpressionStmt*>(node.get());
            return "ExpressionStmt(" + ast_to_string(expr->expression) + ")";
        }
        case ASTNodeType::GUARD_STMT: {
            auto expr = static_cast<GuardStmt*>(node.get());
            return "GuardStmt(" + ast_to_string(expr->condition) + ", " + ast_to_string(expr->elseBranch) + ")";
        }
        case ASTNodeType::RETURN_STMT: {
            auto expr = static_cast<ReturnStmt*>(node.get());
            std::string v;
            if (expr->value) {
                v = ast_to_string(expr->value.value());
            }
            return "ReturnStmt(" + v + ")";
        }
        case ASTNodeType::BLOCK_STMT: {
            auto expr = static_cast<BlockStmt*>(node.get());

            std::string o = "";
            for (auto stmt : expr->statements) {
                o += ast_to_string(stmt);
            }
            return "BlockStmt(" + o + ")";
        }
        case ASTNodeType::IF_STMT: {
            auto expr = static_cast<IfStmt*>(node.get());
            return "IfStmt(" + ast_to_string(expr->condition) + ", " + ast_to_string(expr->thenBranch) + ")";
        }
        case ASTNodeType::FUNCTION_STMT: {
            auto expr = static_cast<FunctionStmt*>(node.get());
            std::string p = "";
            for (auto stmt : expr->params) {
                p += ast_to_string(stmt.first) + ": " + ast_to_string(stmt.second);
            }

            std::string c = "";
            for (auto stmt : expr->body) {
                c += ast_to_string(stmt) + "; ";
            }

            std::string ret = ast_to_string(expr->returnType.value_or(std::make_shared<ASTNode>(Variable("Any"))));

            return "FuncStmt(" + ast_to_string(expr->name) + ", (" + p + "), " + ret + ", {" + c + "})";
        }
        case ASTNodeType::CALL_EXPR: {
            auto expr = static_cast<CallExpr*>(node.get());
            std::string args = "";
            for (auto arg : expr->arguments) {
                args += ast_to_string(arg) + ", ";
            }
            return "CallExpr(" + ast_to_string(expr->callee) + ", (" + args + "))";
        }
        case ASTNodeType::META_STMT: {
            auto expr = static_cast<MetaStmt*>(node.get());
            std::string args = "";
            if (expr->arg.has_value()) {
                for (auto arg : expr->arg.value()) {
                    args += ast_to_string(arg) + ", ";
                }
            }

            return "MetaStmt(" + ast_to_string(expr->ns) + ", " + ast_to_string(expr->call) + ", (" + args + "))";
        }
        case ASTNodeType::NAMESPACE_DECL: {
            auto ns = static_cast<Namespace*>(node.get());
            std::string body = "";
            for (auto stmt : ns->body) {
                body += ast_to_string(stmt) + "; ";
            }

            return "NamespaceStmt(" + ast_to_string(ns->name) + ", (" + body + "))";
        }
        case ASTNodeType::FIELD_ACCESS: {
            auto expr = static_cast<FieldAccess*>(node.get());

            return "FieldAccess(" + ast_to_string(expr->object) + ", " + ast_to_string(expr->field) + ")";
        }
        default:
            return "<unhandled node type '" + std::to_string(static_cast<int>(node->type)) + "'>";
    }
}
