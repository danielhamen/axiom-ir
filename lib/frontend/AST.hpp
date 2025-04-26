#pragma once

#include <string>
#include <memory>
#include <vector>
#include <optional>

// --- AST Node Types ---
enum class ASTNodeType {
    LITERAL,
    VARIABLE,
    BINARY_OP,
    UNARY_OP,
    DECLARATION,
    VARIABLE_PATTERN,
    TUPLE_PATTERN,
    DESTRUCTURE_PATTERN,
    ASSIGNMENT,
    EXPRESSION_STMT,
    PRINT_STMT,
    IF_STMT,
    META_STMT,
    GUARD_STMT,
    WHILE_STMT,
    FOR_IN_STMT,
    BLOCK_STMT,
    FUNCTION_STMT,
    CALL_EXPR,
    RETURN_STMT,
    STRUCT_DECL,
    IMPORT_DECL
};

// --- Base AST Node ---
struct ASTNode {
    ASTNodeType type;
    virtual ~ASTNode();
};

// --- Literal Node ---
struct Literal : ASTNode {
    std::string value;
    explicit Literal(const std::string& val);
    bool is_str();
    bool is_int();
    bool is_dec();
};

// --- Variable Reference Node ---
struct Variable : ASTNode {
    std::string name;
    explicit Variable(const std::string& n);
};

// --- Binary Operation Node ---
struct BinaryOp : ASTNode {
    std::string op;
    std::shared_ptr<ASTNode> left, right;
    BinaryOp(const std::string& oper,
             std::shared_ptr<ASTNode> lhs,
             std::shared_ptr<ASTNode> rhs);
};

// --- Unary Operation Node ---
struct UnaryOp : ASTNode {
    std::string op;
    std::shared_ptr<ASTNode> operand;
    UnaryOp(const std::string& oper,
            std::shared_ptr<ASTNode> opd);
};

// --- Declaration (let or const) Node ---
struct Declaration : public ASTNode {
    std::shared_ptr<ASTNode> pattern;
    std::optional<std::string> type_annotation;
    std::optional<std::shared_ptr<ASTNode>> initializer;

    Declaration(std::shared_ptr<ASTNode> pattern,
                std::optional<std::string> type_annotation,
                std::optional<std::shared_ptr<ASTNode>> initializer);
};

// --- VariablePattern Node ---
struct VariablePattern : public ASTNode {
    std::string name;

    VariablePattern(const std::string& name);
};

// --- TuplePattern Node ---
struct TuplePattern : public ASTNode {
    std::vector<std::string> names;

    TuplePattern(std::vector<std::string> names);
};

// --- DestructurePattern Node ---
struct DestructurePattern : public ASTNode {
    std::vector<std::string> names;
    bool isArray; // true = array destructuring, false = object destructuring

    DestructurePattern(std::vector<std::string> names, bool isArray);
};

// --- Assignment Node ---
struct Assignment : ASTNode {
    std::string name;
    std::shared_ptr<ASTNode> value;
    Assignment(const std::string& n,
               std::shared_ptr<ASTNode> val);
};

// --- Expression Statement Node ---
struct ExpressionStmt : ASTNode {
    std::shared_ptr<ASTNode> expression;
    explicit ExpressionStmt(std::shared_ptr<ASTNode> expr);
};

// --- If Statement Node ---
struct IfStmt : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> thenBranch;
    std::vector<std::shared_ptr<ASTNode>> elifBranches;
    std::optional<std::shared_ptr<ASTNode>> elseBranch;

    IfStmt(std::shared_ptr<ASTNode> cond,
           std::shared_ptr<ASTNode> thenB,
           std::vector<std::shared_ptr<ASTNode>> elifB = {},
           std::optional<std::shared_ptr<ASTNode>> elseB = std::nullopt);
};

// --- Meta NS Call ---
//  e.g. Meta::RAW_EMIT("(WRITE)");
struct MetaStmt : ASTNode {
    std::shared_ptr<ASTNode> ns; // namespace (i.e. 'Meta')
    std::shared_ptr<ASTNode> call; // e.g. 'RAW_EMIT'
    std::optional<std::vector<std::shared_ptr<ASTNode>>> arg; // if set, call function; else treat as var

    MetaStmt(
        std::shared_ptr<ASTNode> ns,
        std::shared_ptr<ASTNode> call,
        std::optional<std::vector<std::shared_ptr<ASTNode>>> arg
    );

    MetaStmt(
        std::shared_ptr<ASTNode> ns,
        std::shared_ptr<ASTNode> call
    );
};

struct ElifBranch : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> thenBranch;
};

// --- Guard Statement Node ---
struct GuardStmt : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> elseBranch;
    GuardStmt(std::shared_ptr<ASTNode> cond,
           std::shared_ptr<ASTNode> elseB);
};

// --- While Statement Node ---
struct WhileStmt : ASTNode {
    std::shared_ptr<ASTNode> condition;
    std::shared_ptr<ASTNode> body;
    WhileStmt(std::shared_ptr<ASTNode> cond,
              std::shared_ptr<ASTNode> b);
};

// --- For-In Statement Node ---
struct ForInStmt : ASTNode {
    std::string varName;
    std::shared_ptr<ASTNode> iterable;
    std::shared_ptr<ASTNode> body;
    ForInStmt(const std::string& n,
              std::shared_ptr<ASTNode> iter,
              std::shared_ptr<ASTNode> b);
};

// --- Block Statement Node ---
struct BlockStmt : ASTNode {
    std::vector<std::shared_ptr<ASTNode>> statements;
    explicit BlockStmt(std::vector<std::shared_ptr<ASTNode>> stmts);
};

// --- Function Declaration Node ---
struct FunctionStmt : ASTNode {
    std::shared_ptr<ASTNode> name;
    std::vector<std::pair<std::shared_ptr<ASTNode>, std::shared_ptr<ASTNode>>> params; // (paramName, paramType)
    std::optional<std::shared_ptr<ASTNode>> returnType;
    std::vector<std::shared_ptr<ASTNode>> body; // Function body block

    FunctionStmt(
        std::shared_ptr<ASTNode> name,
        std::vector<std::pair<std::shared_ptr<ASTNode>, std::shared_ptr<ASTNode>>> params,
        std::optional<std::shared_ptr<ASTNode>> returnType,
        std::vector<std::shared_ptr<ASTNode>> body
    );
};

// --- Access Node (e.g. "Math.sin") ---
struct FieldAccess : ASTNode {
    std::shared_ptr<ASTNode> object;
    std::string field;

    FieldAccess(std::shared_ptr<ASTNode> object, const std::string& field);
};

// --- Call Expression Node ---
struct CallExpr : ASTNode {
    std::shared_ptr<ASTNode> callee;
    std::vector<std::shared_ptr<ASTNode>> arguments;
    CallExpr(std::shared_ptr<ASTNode> c,
             std::vector<std::shared_ptr<ASTNode>> args);
};

// --- Return Statement Node ---
struct ReturnStmt : ASTNode {
    std::optional<std::shared_ptr<ASTNode>> value;
    explicit ReturnStmt(std::optional<std::shared_ptr<ASTNode>> v = std::nullopt);
};

// --- Struct Declaration Node ---
struct StructDecl : ASTNode {
    std::string name;
    std::vector<std::string> fields;
    StructDecl(const std::string& n,
               std::vector<std::string> f);
};

// --- Import Declaration Node ---
struct ImportDecl : ASTNode {
    std::string module;
    std::optional<std::string> alias;
    ImportDecl(const std::string& m,
               std::optional<std::string> a = std::nullopt);
};

std::string ast_to_string(const std::shared_ptr<ASTNode>& node);
