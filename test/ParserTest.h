#pragma once
#include <gtest/gtest.h>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Error.h"

class ParserTest : public ::testing::Test {
protected:
    std::map<std::string, double> table;
    Lexer lexer;
    std::istringstream input;
    std::unique_ptr<Parser> parser;

    void SetUp() override {
        // parser 会在每次 evaluate 时重新构造
    }

    double evaluate(const std::string& expr) {
        input.str(expr + "\n");
        input.clear();
        lexer.getToken(input);  // 初始化 currToken

        parser = std::make_unique<Parser>(lexer, input, table);
        return parser->expr(false); // 不需要主动推进，因为已经在上面getToken了
    }
};