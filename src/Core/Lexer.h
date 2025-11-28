#pragma once
#include <string>

enum class TokenType {
    NUMBER = 1,
    NAME = 2,
    END = 0,
    PLUS = '+',      // 43
    MINUS = '-',     // 45
    MUL = '*',       // 42
    DIV = '/',       // 47
    PRINT = ';',     // 59
    ASSIGN = '=',    // 61
    LP = '(',        // 40
    RP = ')'         // 41
};

class Lexer {
public:
    TokenType currToken;
    double numberValue;
    std::string stringValue;

    TokenType getToken(std::istream& in);
};