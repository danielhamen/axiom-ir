#include <string>
#include <random>
#include <any>
#include <iostream>
#include "Emitter.hpp"
#include <stdexcept>
#include <vector>
#include <memory>

Emitter::Emitter(std::vector<std::shared_ptr<ASTNode>>& program)
    : program(program) {}

std::vector<Bytecode> Emitter::emit() {
    std::vector<Bytecode> main; // .main entry code
    std::vector<Bytecode> structural; // passive code like definitions of functions, classes, etc
    main.push_back({OP_LABEL, {".main"}});

    for (const auto& node : program) {
        auto code = emit_node(node);
        for (auto b : code) {
            // std::cout << b.toString() << std::endl;
            if (node->type == ASTNodeType::FUNCTION_STMT) {
                structural.push_back(b);
            } else {
                main.push_back(b);
            }
        }
    }

    main.push_back({OP_EXIT, {}});

    std::vector<Bytecode> result;
    result.insert(result.begin(), structural.begin(), structural.end());
    result.insert(result.end(), main.begin(), main.end());
    return result;
}

std::vector<Bytecode> Emitter::emit_node(const std::shared_ptr<ASTNode>& node) {
    switch (node->type) {
        case ASTNodeType::DECLARATION:
            return emit_declaration(std::static_pointer_cast<Declaration>(node));
        case ASTNodeType::LITERAL:
            return emit_literal(std::static_pointer_cast<Literal>(node));
        case ASTNodeType::BINARY_OP:
            return emit_binary_op(std::static_pointer_cast<BinaryOp>(node));
        case ASTNodeType::VARIABLE:
            return emit_variable(std::static_pointer_cast<Variable>(node));
        case ASTNodeType::IF_STMT:
            return emit_if_stmt(std::static_pointer_cast<IfStmt>(node));
        case ASTNodeType::META_STMT:
            return emit_meta_stmt(std::static_pointer_cast<MetaStmt>(node));
        case ASTNodeType::FUNCTION_STMT:
            return emit_function_stmt(std::static_pointer_cast<FunctionStmt>(node));
        case ASTNodeType::RETURN_STMT:
            return emit_return(std::static_pointer_cast<ReturnStmt>(node));
        case ASTNodeType::CALL_EXPR:
            return emit_call_expr(std::static_pointer_cast<>());
        default:
            std::cout << ast_to_string(node) << std::endl;
            throw std::runtime_error("<unknown AST node type>");
    }
}

std::string random_identifier(size_t length = 12) {
    static const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string result = "_";
    result.reserve(length);
    for (size_t i = 0; i < length - 1; ++i) {
        result += chars[dist(rng)];
    }
    return result;
}

std::vector<Bytecode> Emitter::emit_function_stmt(const std::shared_ptr<FunctionStmt>& funcStmt) {
    std::vector<Bytecode> code;

    std::string ref_name = "." + random_identifier();

    auto func_name = std::dynamic_pointer_cast<Variable>(funcStmt->name);

    // --- Function entry label ---
    code.push_back({ OP_LABEL, { "." + func_name->name } });
    code.push_back({ OP_JMP, { ref_name } });

    // --- Function body label ---
    code.push_back({ OP_LABEL, { ref_name } });

    // Emit function body
    for (auto stmt : funcStmt->body) {
        auto stmt_code = emit_node(stmt);
        code.insert(code.end(), stmt_code.begin(), stmt_code.end());
    }

    // Function return
    code.push_back({ OP_RET, {} });
    code.push_back({ OP_END, {} });

    return code;
}

std::vector<Bytecode> Emitter::emit_return(const std::shared_ptr<ReturnStmt>& retStmt) {
    std::vector<Bytecode> code;

    if (retStmt->value.has_value()) {
        auto value = retStmt->value.value();
        auto value_code = emit_node(value);
        code.insert(code.end(), value_code.begin(), value_code.end());
    }

    return code;
}

std::vector<Bytecode> Emitter::emit_meta_stmt(const std::shared_ptr<MetaStmt>& metaStmt) {
    std::vector<Bytecode> code;

    // Correctly cast ASTNode -> Variable
    auto ns = std::dynamic_pointer_cast<Variable>(metaStmt->ns);
    if (!ns) {
        throw std::runtime_error("MetaStmt ns is not a Variable.");
    }

    auto callee_var = std::dynamic_pointer_cast<Variable>(metaStmt->call);
    if (!callee_var) {
        throw std::runtime_error("MetaStmt call is not a Variable.");
    }

    auto callee = callee_var->name;
    auto args = metaStmt->arg;

    // Functions
    if (args.has_value()) {
        if (callee == "Emit") {
            if (!args.has_value() || args->size() != 1) {
                throw std::runtime_error("Meta.Emit(...) expects exactly one argument. Given: " + (args ? std::to_string(args->size()) : "none"));
            }

            auto first_arg = args->at(0);
            auto lit = std::dynamic_pointer_cast<Literal>(first_arg);
            if (!lit) {
                throw std::runtime_error("Meta.Emit(...) expects a literal string argument.");
            }

            if (!lit->is_str()) {
                throw std::runtime_error("Meta.Emit(...) expects a single string argument.");
            }

            std::string raw_code = lit->value;
            str_decode(raw_code);
            std::vector<Bytecode> code = parse_raw_bytecode(raw_code);
            return code;
        }
        if (callee == "Time") {
            if (!args.has_value() || args->size() != 0) {
                throw std::runtime_error("Meta.Time() expects exactly zero arguments. Given: " + (args ? std::to_string(args->size()) : "none"));
            }

            std::vector<Bytecode> code = parse_raw_bytecode("(TIME)");
            return code;
        }
        if (callee == "Random") {
            if (!args.has_value() || args->size() != 0) {
                throw std::runtime_error("Meta.Random() expects exactly zero arguments. Given: " + (args ? std::to_string(args->size()) : "none"));
            }

            std::vector<Bytecode> code = parse_raw_bytecode("(RAND)");
            return code;
        }
        if (callee == "Write") {
            if (!args.has_value() || args->size() != 0) {
                throw std::runtime_error("Meta.Write() expects exactly zero arguments. Given: " + (args ? std::to_string(args->size()) : "none"));
            }

            std::vector<Bytecode> code = parse_raw_bytecode("(WRITE)");
            return code;
        }
        if (callee == "Flush") {
            if (!args.has_value() || args->size() != 0) {
                throw std::runtime_error("Meta.Flush() expects exactly zero arguments. Given: " + (args ? std::to_string(args->size()) : "none"));
            }

            std::vector<Bytecode> code = parse_raw_bytecode("(FLUSH)");
            return code;
        }
        if (callee == "Dump") {
            if (!args.has_value() || args->size() != 0) {
                throw std::runtime_error("Meta.Dump() expects exactly zero arguments. Given: " + (args ? std::to_string(args->size()) : "none"));
            }

            std::vector<Bytecode> code = parse_raw_bytecode("(DUMP)");
            return code;
        }
    }
    // Properties
    else {
        // Handle property access...
    }

    throw std::runtime_error("Unexpected Meta call: '" + callee + "'");
}

std::vector<Bytecode> Emitter::emit_if_stmt(const std::shared_ptr<IfStmt>& var) {
    std::vector<Bytecode> code;

    return code;
}

std::vector<Bytecode> Emitter::emit_variable(const std::shared_ptr<Variable>& var) {
    std::vector<Bytecode> code;
    code.push_back({ OP_GET, { "$" + var->name } });

    return code;
}

std::vector<Bytecode> Emitter::emit_binary_op(const std::shared_ptr<BinaryOp>& binop) {
    std::vector<Bytecode> code;
    Opcode o;
    if (binop->op == "+") {
        o = Opcode::OP_ADD;
    } else if (binop->op == "-") {
        o = Opcode::OP_SUB;
    } else if (binop->op == "*") {
        o = Opcode::OP_MUL;
    } else if (binop->op == "/") {
        o = Opcode::OP_DIV;
    } else if (binop->op == "%") {
        o = Opcode::OP_MOD;
    } else if (binop->op == "&&") {
        o = Opcode::OP_AND;
    } else if (binop->op == "||") {
        o = Opcode::OP_OR;
    }

    // left side
    auto left_code = emit_node(binop->left);
    code.insert(code.end(), left_code.begin(), left_code.end());

    // right side
    auto right_code = emit_node(binop->right);
    code.insert(code.end(), right_code.begin(), right_code.end());

    code.push_back(Bytecode{ o, {} });

    return code;
}

std::vector<Bytecode> Emitter::emit_literal(const std::shared_ptr<Literal>& literal) {
    std::vector<Bytecode> code;

    auto lit = static_cast<Literal*>(literal.get());
    std::string value = lit->value;
    if (lit->is_str()) {
        str_encode(value);
    }

    code.push_back({
        OP_PUSH,
        {value}
    });

    return code;
}

std::vector<Bytecode> Emitter::emit_declaration(const std::shared_ptr<Declaration>& decl) {
    std::vector<Bytecode> code;

    auto pattern = std::dynamic_pointer_cast<VariablePattern>(decl->pattern);
    if (!pattern) {
        throw std::runtime_error("Only simple variable declarations are supported for now.");
    }

    const std::string& name = pattern->name;
    std::string type = decl->type_annotation.value_or("Any");

    // Step 1: Declare the variable (before any value is assigned!)
    code.push_back(Bytecode{ OP_DECL, { "$" + name } });

    // Step 2: Annotate its type
    code.push_back(Bytecode{ OP_TYPE, { "$" + name, type } });

    // Step 3: If initializer exists, assign value into it
    if (decl->initializer.has_value()) {
        // 3a: emit code to compute the initializer
        auto init_code = emit_node(decl->initializer.value());
        code.insert(code.end(), init_code.begin(), init_code.end());

        // 3b: after computing, set it into variable
        code.push_back(Bytecode{ OP_SET, { "$" + name } });
    }

    return code;
}
