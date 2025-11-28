#pragma once

#include <gtest/gtest.h>
#include <sstream>
#include "Lexer.h"

class LexerTest : public ::testing::Test {
protected:
    Lexer lexer;
    std::istringstream input;

    TokenType nextToken(const std::string& expr) {
        input.str(expr);
        input.clear();
        return lexer.getToken(input);
    }
};