#pragma once
#include "parse_literal.hpp"
std::shared_ptr<Object> parse_literal(const std::string& tok) {
     // if (tok == "true")  return std::make_shared<Bool>(true);
     // if (tok == "false") return std::make_shared<Bool>(false);
     // if (tok == "null") return std::make_shared<Null>();
     // if (tok == "undefined") return std::make_shared<Undefined>();
     // if (tok == "nan" || tok == "NaN") return std::make_shared<NaN>();
     // if (tok == "inf" || tok == "infinity") return std::make_shared<Infinity>();

     if ((tok.front() == '"' && tok.back() == '"') ||
         (tok.front() == '\'' && tok.back() == '\''))
     {
         // return std::make_shared<String>(tok.substr(1, tok.size() - 2));
     }

     bool negative = false;
     size_t start = 0;
     if (!tok.empty() && (tok[0] == '+' || tok[0] == '-')) {
         negative = (tok[0] == '-');
         start = 1;
     }

     // Check for decimal
     if (tok.find('.', start) != std::string::npos) {
         double val = std::stod(tok);
         // return std::make_shared<Decimal>(val);
     }

     // Integer literal
     std::string digits = tok.substr(start);
     if (!std::all_of(digits.begin(), digits.end(), ::isdigit))
         throw std::runtime_error("Invalid numeric literal: " + tok);

     uint64_t val = std::stoull(digits);
     // return std::make_shared<Integer>(val, !negative);
 }
