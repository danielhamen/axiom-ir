#include "axiom/Base/BaseInstruction.hpp"
#include "axiom/Base/BaseObject.hpp"
#include "axiom/Globals.hpp"
#include "./lib/ir/ext/obj/FloatObject.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <ratio>
#include <string>
#include <fstream>
#include <sstream>
#include <axiom/Process.hpp>
#include "lib/ir/ext/__init__.hpp"
#include "lib/ir/ext/obj/StrObject.hpp"
#include <axiom/VMContext.hpp>
#include <vector>
#include <cctype>
#include <unordered_map>

enum class TokenType {
    Literal,
    String,
    Call
};

struct Token {
    TokenType type;
    std::string text;   // for String tokens, this holds the *unescaped* content
};

static std::string unescape(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            switch (s[i+1]) {
                case 'n':  out += '\n'; break;
                case 't':  out += '\t'; break;
                case '"':  out += '"';  break;
                case '\\': out += '\\'; break;
                default:   out += s[i+1]; break;
            }
            i++;
        } else {
            out += s[i];
        }
    }
    return out;
}

static std::vector<Token> tokenize(const std::string& line) {
    std::vector<Token> tokens;
    size_t i = 0, n = line.size();
    while (i < n) {
        // skip whitespace
        if (std::isspace(line[i])) {
            ++i;
            continue;
        }

        // String literal
        if (line[i] == '"') {
            ++i;
            std::string raw;
            while (i < n) {
                if (line[i] == '\\' && i + 1 < n) {
                    raw += line[i];     // keep escape markers so we can unescape later
                    raw += line[i+1];
                    i += 2;
                } else if (line[i] == '"') {
                    ++i;  // consume closing quote
                    break;
                } else {
                    raw += line[i++];
                }
            }
            tokens.push_back({ TokenType::String, unescape(raw) });
            continue;
        }

        // Call directive
        if (line[i] == '#') {
            size_t start = i++;
            while (i < n && !std::isspace(line[i])) ++i;
            tokens.push_back({ TokenType::Call, line.substr(start, i - start) });
            continue;
        }

        // Literal (identifiers, numbers, booleans, etc.)
        {
            size_t start = i;
            while (i < n && !std::isspace(line[i])) ++i;
            tokens.push_back({ TokenType::Literal, line.substr(start, i - start) });
        }
    }
    return tokens;
}


std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos) return ""; // All whitespace or empty

    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}


std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void parse_process(const std::vector<std::string>& lines, Process& process) {
    for (const auto& line : lines) {
        auto tokens = tokenize(line);
        if (tokens.empty()) continue;

        // --- Opcode ---
        if (tokens[0].type != TokenType::Literal)
            throw std::runtime_error("Expected instruction name, got: '" + tokens[0].text + "'");
        auto opcode = tokens[0].text;

        if (!Globals::instance().instructions.has(opcode))
            throw std::runtime_error("Use of unregistered instruction: '" + opcode + "'");

        // --- Arguments ---
        std::vector<ObjectPtr> args;
        for (size_t i = 1; i < tokens.size(); ++i) {
            const auto& tk = tokens[i];
            if (tk.text.empty()) continue;

            switch (tk.type) {
                case TokenType::Literal: {
                    // numbers, booleans, identifiers, etc.
                    auto lit = Globals::instance().literals.find_matching(tk.text);
                    args.push_back(lit->parse(tk.text));
                    break;
                }
                case TokenType::String: {
                    // string literal
                    args.push_back(std::make_shared<StrObject>(tk.text));
                    break;
                }
                case TokenType::Call:
                    throw std::runtime_error("Unexpected call-directive in instruction args: '" + tk.text + "'");
            }
        }

        // --- Build & enqueue instruction ---
        process.pt.push_back(Globals::instance()
                                 .instructions
                                 .create(opcode, args));
    }

    // Preload math constants as immutable (type = 1)
    process.vm.declare("E",  std::make_shared<FloatObject>(2.718281828459045), 1);
    process.vm.declare("PI", std::make_shared<FloatObject>(3.141592653589793), 1);
}



int run_file(const std::string& path) {
    init_ext();

    // 1) Read + trim all non-empty lines
    std::vector<std::string> all_lines;
    {
        std::ifstream in(path);
        if (!in) throw std::runtime_error("Cannot open file: " + path);
        std::string raw;
        while (std::getline(in, raw)) {
            auto line = trim(raw);
            if (!line.empty()) all_lines.push_back(line);
        }
    }

    // 2) Split into per-thread Processes
    size_t i = 0;
    while (i < all_lines.size()) {
        auto header_tokens = tokenize(all_lines[i]);
        if (header_tokens.size() >= 2 &&
            header_tokens[0].type == TokenType::Call &&
            header_tokens[0].text == "#THREAD" &&
            header_tokens[1].type == TokenType::Literal)
        {
            int thread_id = std::stoi(header_tokens[1].text);
            ++i;

            // Collect until #KILL
            std::vector<std::string> thread_lines;
            while (i < all_lines.size()) {
                auto tkn = tokenize(all_lines[i]);
                if (!tkn.empty() &&
                    tkn[0].type == TokenType::Call &&
                    tkn[0].text == "#KILL")
                {
                    // build and store this thread
                    Process p;
                    parse_process(thread_lines, p);
                    p.pt.push_back(Globals::instance().instructions.create("EXIT"));
                    Globals::instance().threads.emplace(thread_id, std::move(p));
                    ++i;
                    break;
                }

                thread_lines.push_back(all_lines[i]);
                ++i;
            }
        }
        else {
            // skip any top-level lines that aren't thread markers
            ++i;
        }
    }

    // 3) Dispatch main thread (id == 0)
    auto it = Globals::instance().threads.find(0);
    if (it == Globals::instance().threads.end())
        throw std::runtime_error("No main thread (#THREAD 0) found");
    it->second.dispatch();

    return 0;
}

int main(int argc, char* argv[]) {
    std::cout << "axiom-cli.exe ~ version 1.0.0" << std::endl;

    if (argc < 2) {
        std::cerr << "Usage: axiom-cli <file.axb>" << std::endl;
        return 1;
    }

    int code = run_file(argv[1]);
    if (code == 0) {
        std::cout << std::endl << "--- Execution completed successfully ---" << std::endl;
    } else {
        std::cout << std::endl << "--- Execution with error ---" << std::endl;
    }
    return code;
}
