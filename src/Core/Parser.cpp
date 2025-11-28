#include "Parser.h"
#include "Error.h"

Parser::Parser(Lexer& lexer, std::istream& input, std::map<std::string, double>& table)
    : lexer(lexer), input(input), table(table) {}

double Parser::expr(bool get) {
    double left = term(get);

    while (true) {
        switch (lexer.currToken) {
        case TokenType::PLUS:
            left += term(true);
            continue;
        case TokenType::MINUS:
            left -= term(true);
            continue;
        default:
            return left;
        }
    }
}

double Parser::term(bool get) {
    double left = prim(get);

    while (true) {
        switch (lexer.currToken) {
        case TokenType::MUL:
            left *= prim(true);
            continue;
        case TokenType::DIV: {
            double divisor = prim(true);
            if (divisor == 0.0) throw ZeroDivide();
            left /= divisor;
            continue;
        }
        default:
            return left;
        }
    }
}

double Parser::prim(bool get) {
    if (get) lexer.getToken(input);

    switch (lexer.currToken) {
    case TokenType::NUMBER: {
        double value = lexer.numberValue;
        lexer.getToken(input);
        return value;
    }
    case TokenType::NAME: {
        std::string name = lexer.stringValue;
        TokenType op = lexer.getToken(input);
        if (op == TokenType::ASSIGN) {
            double val = expr(true);
            table[name] = val;
            return val;
        }
        return table[name];
    }
    case TokenType::MINUS: {
        double val = prim(true);
        return -val;
    }
    case TokenType::LP: {
        double value = expr(true);
        if (lexer.currToken != TokenType::RP)
            throw SyntaxError("')' expected");
        lexer.getToken(input);
        return value;
    }
    default:
        throw SyntaxError("primary expected");
    }
}