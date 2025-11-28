#include "Lexer.h"
#include <cctype>
#include <iostream>

TokenType Lexer::getToken(std::istream& in) {
    char ch;
    do {
        if (!in.get(ch)) return currToken = TokenType::END;
    } while (isspace(ch));

    switch (ch) {
    case '+': return currToken = TokenType::PLUS;
    case '-': return currToken = TokenType::MINUS;
    case '*': return currToken = TokenType::MUL;
    case '/': return currToken = TokenType::DIV;
    case ';': return currToken = TokenType::PRINT;
    case '(': return currToken = TokenType::LP;
    case ')': return currToken = TokenType::RP;
    case '=': return currToken = TokenType::ASSIGN;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.': {
        in.putback(ch);
        in >> numberValue;
        return currToken = TokenType::NUMBER;
    }

    default:
        if (isalpha(ch) || ch == '_') {
            stringValue = ch;
            while (in.get(ch) && (isalnum(ch) || ch == '_')) stringValue += ch;
            in.putback(ch);
            return currToken = TokenType::NAME;
        }
        return currToken = TokenType::END;
    }
}