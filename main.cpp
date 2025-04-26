#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "lib/emitter/Emitter.hpp"
#include "lib/frontend/AST.hpp"
#include "lib/frontend/Desugarer.hpp"
#include "lib/frontend/Token.hpp"
#include "lib/vm/core/Bytecode.hpp"
#include "lib/vm/core/Process.hpp"
#include "lib/frontend/Lexer.hpp"
#include "lib/frontend/Parser.hpp"
#include "lib/vm/core/opmap.hpp"
#include "lib/vm/helpers/get_nanotime.hpp"

std::string reverse_opmap(Opcode& code) {
    for (auto kv : opmap) {
        if (kv.second == code)
            return kv.first;
    }

    throw std::runtime_error("Incorrect code.");
}

int main() {
    // std::cout << std::endl << std::endl << "--- Program Begin ---" << std::endl;
    std::string filepath = "test.axs";
    std::ifstream File(filepath);
    std::string raw_code;
    while (!File.eof()) {
        std::string line;
        std::getline(File, line);
        raw_code += line + "\n";
    }

    // std::cout << "Retieved contents of file." << std::endl;

    // --- LEXER  ---
    int start = get_nanotime();
    Lexer lexer(raw_code);
    std::vector<Token> tokens = lexer.tokenize();

    // std::cout << "Tokenized code:" << std::endl;

    // for (auto tok : tokens) {
    //     std::cout << "\t" << "['" << tok.lexeme << "']" << std::endl;
    // }

    // std::cout << std::endl;

    // --- PARSER ---
    Parser parser(tokens);
    std::vector<std::shared_ptr<ASTNode>> ast = parser.parse();

    // std::cout << "Parsed code." << std::endl;

    // --- DESUGARING ---
    Desugarer desugarer(ast);
    std::vector<std::shared_ptr<ASTNode>> ast_simple = desugarer.desugar();


    // std::cout << "Desugared code:" << std::endl;

    // for (auto node : ast_simple) {
    //     std::cout << "\t" << ast_to_string(node) << std::endl;
    // }

    // --- SEMANTIC ANALYSIS ---

    // --- CODE EMISSION ---
    Emitter emitter(ast_simple);
    std::vector<Bytecode> code = emitter.emit();

    // for (auto b : code) {
    //     std::cout << b.toString() << std::endl;
    // }

    // ---
    Process proc(code);
    proc.execute();
    int end = get_nanotime();
    std::cout << "Executed the Program in " << end - start << " nanoseconds" << std::endl;
    return 0;
}
