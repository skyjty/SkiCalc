#include "LexerTest.h"
#include "Error.h"

// 数字token测试
TEST_F(LexerTest, TokenizeNumber) {
    // 整数测试
    EXPECT_EQ(nextToken("31"), TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(lexer.numberValue, 31.0);

    // 浮点数测试
    EXPECT_EQ(nextToken("3.14"), TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(lexer.numberValue, 3.14);
}

// 运算符token测试
TEST_F(LexerTest, TokenizeOperators) {
    EXPECT_EQ(nextToken("+"), TokenType::PLUS);
    EXPECT_EQ(nextToken("-"), TokenType::MINUS);
    EXPECT_EQ(nextToken("*"), TokenType::MUL);
    EXPECT_EQ(nextToken("/"), TokenType::DIV);
}

// 括号token测试
TEST_F(LexerTest, TokenizeParentheses) {
    EXPECT_EQ(nextToken("("), TokenType::LP);
    EXPECT_EQ(nextToken(")"), TokenType::RP);
}

// 赋值运算符token测试
TEST_F(LexerTest, TokenizeAssignment) {
    EXPECT_EQ(nextToken("="), TokenType::ASSIGN);
}

// 标识符token测试
TEST_F(LexerTest, TokenizeIdentifier) {
    // 单字符标识符
    EXPECT_EQ(nextToken("x"), TokenType::NAME);
    EXPECT_EQ(lexer.stringValue, "x");

    // 多字符标识符（含数字）
    EXPECT_EQ(nextToken("var123"), TokenType::NAME);
    EXPECT_EQ(lexer.stringValue, "var123");

    // 下划线开头
    EXPECT_EQ(nextToken("_temp"), TokenType::NAME);
    EXPECT_EQ(lexer.stringValue, "_temp");
}

// 空白字符处理测试
TEST_F(LexerTest, SkipWhitespace) {
    // 普通空格
    EXPECT_EQ(nextToken("   7"), TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(lexer.numberValue, 7.0);

    // 制表符和换行符
    EXPECT_EQ(nextToken("\t\n\r8"), TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(lexer.numberValue, 8.0);
}

// 输入结束测试
TEST_F(LexerTest, TokenizeEndOfInput) {
    EXPECT_EQ(nextToken(""), TokenType::END);
    EXPECT_EQ(nextToken("  "), TokenType::END);
}

// 多token序列测试
TEST_F(LexerTest, TokenizeMultipleTokens) {
    input.str("x = 3 + 4");
    input.clear();

    // 验证完整表达式的token序列
    EXPECT_EQ(lexer.getToken(input), TokenType::NAME);
    EXPECT_EQ(lexer.stringValue, "x");
    EXPECT_EQ(lexer.getToken(input), TokenType::ASSIGN);
    EXPECT_EQ(lexer.getToken(input), TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(lexer.numberValue, 3.0);
    EXPECT_EQ(lexer.getToken(input), TokenType::PLUS);
    EXPECT_EQ(lexer.getToken(input), TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(lexer.numberValue, 4.0);

    EXPECT_EQ(lexer.getToken(input), TokenType::END);
}

// 非法字符处理测试：遇到未知字符应该抛出 SyntaxError
TEST_F(LexerTest, TokenizeIllegalCharacter) {
    input.str("@");
    input.clear();
    EXPECT_THROW(lexer.getToken(input), SyntaxError);
}

// 非 ASCII 输入（例如中文）应被视为非法字符序列，词法器应至少对第一个字节抛出 SyntaxError
TEST_F(LexerTest, TokenizeNonAsciiInput) {
    // UTF-8 多字节中文字符串
    input.str("中文");
    input.clear();
    EXPECT_THROW(lexer.getToken(input), SyntaxError);
}