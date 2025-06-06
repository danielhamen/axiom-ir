#include "parse_literal.hpp"
#include <cctype> // for std::isdigit
#include <stdexcept>

std::shared_ptr<Object> parse_literal(const std::string& tok) {
    // --- Booleans ---
    if (tok == "true")  return std::make_shared<Boolean>(true);
    if (tok == "false") return std::make_shared<Boolean>(false);

    // --- Indefinites ---
    if (tok == "nil") return Nil::instance();
    if (tok == "nix") return Nix::instance();
    if (tok == "nan") return NaN::instance();


    // --- Regular Expression Literals ---
    if (tok.size() >= 4 && tok[0] == 'r' && tok[1] == '/' && tok.find('/', 2) != std::string::npos) {
        auto lastSlash = tok.rfind('/');
        std::string pattern = tok.substr(2, lastSlash - 2);
        std::string flagsStr = tok.substr(lastSlash + 1);
        std::set<char> flags(flagsStr.begin(), flagsStr.end());
        return std::make_shared<RegEx>(pattern, flags);
    }

    // --- String Literals ---
    if (tok.size() >= 2 &&
        ((tok.front() == '"' && tok.back() == '"') ||
         (tok.front() == '\'' && tok.back() == '\''))) {
        std::string _tok = tok;
        str_decode(_tok);
        return std::make_shared<String>(_tok);
    }

    // --- Numeric Literals ---
    {
        size_t start = 0;
        if (tok[0] == '+' || tok[0] == '-') start = 1;

        bool hasDot = false;
        bool hasExp = false;
        for (size_t i = start; i < tok.size(); ++i) {
            if (tok[i] == '.') {
                if (hasDot) {
                    throw std::runtime_error("Invalid number: multiple dots in " + tok);
                }
                hasDot = true;
            }
            else if (tok[i] == 'e' || tok[i] == 'E') {
                if (hasExp) {
                    throw std::runtime_error("Invalid number: multiple exponents in " + tok);
                }
                hasExp = true;
            }
            else if (!std::isdigit(static_cast<unsigned char>(tok[i]))) {
                throw std::runtime_error("Invalid character '" + std::string(1, tok[i]) + "' in numeric literal: " + tok);
            }
        }

        try {
            if (hasDot) {
                double v = std::stod(tok);
                return std::make_shared<Float>(v);
            }
            int64_t v = std::stoll(tok);
            return std::make_shared<Integer>(v);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Failed to parse numeric literal: " + tok);
        }
    }

    throw std::runtime_error("Invalid literal: " + tok);
}
