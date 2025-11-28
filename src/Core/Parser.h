#pragma once
#include "Lexer.h"
#include <map>

class Parser {
public:
    Parser(Lexer& lexer, std::istream& input, std::map<std::string, double>& table);

    double expr(bool get);
    double term(bool get);
    double prim(bool get);

private:
    Lexer& lexer;
    std::istream& input;
    std::map<std::string, double>& table;
};