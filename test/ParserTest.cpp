#include "ParserTest.h"

// 数字常量
TEST_F(ParserTest, ParseNumber) {
    EXPECT_DOUBLE_EQ(evaluate("42"), 42.0);
}

// 负号
TEST_F(ParserTest, ParseNegative) {
    EXPECT_DOUBLE_EQ(evaluate("-5"), -5.0);
}

// 加法
TEST_F(ParserTest, ParseAddition) {
    EXPECT_DOUBLE_EQ(evaluate("3 + 4"), 7.0);
}

// 运算符优先级
TEST_F(ParserTest, ParsePrecedence) {
    EXPECT_DOUBLE_EQ(evaluate("3 + 4 * 2"), 11.0);
}

// 括号优先级
TEST_F(ParserTest, ParseParentheses) {
    EXPECT_DOUBLE_EQ(evaluate("(3 + 4) * 2"), 14.0);
}

// 变量赋值
TEST_F(ParserTest, VariableAssignment) {
    EXPECT_NO_THROW({
        double result = evaluate("x = 10");
        EXPECT_DOUBLE_EQ(result, 10.0);
        EXPECT_DOUBLE_EQ(table["x"], 10.0);
    });
}

// 变量引用
TEST_F(ParserTest, VariableReference) {
    table["x"] = 7.5;
    EXPECT_DOUBLE_EQ(evaluate("x"), 7.5);
}

// 除法
TEST_F(ParserTest, Division) {
    EXPECT_DOUBLE_EQ(evaluate("8 / 2"), 4.0);
}

// 除零异常
TEST_F(ParserTest, DivisionByZeroThrows) {
    EXPECT_THROW(evaluate("5 / 0"), ZeroDivide);
}

// 语法错误
TEST_F(ParserTest, SyntaxErrorThrows) {
    EXPECT_THROW(evaluate("3 + "), SyntaxError);
}

// 多层嵌套括号
TEST_F(ParserTest, NestedParentheses) {
    EXPECT_DOUBLE_EQ(evaluate("((2 + 3) * (4 - 1))"), 15.0);
}

// 变量覆盖
TEST_F(ParserTest, VariableOverwrite) {
    table["x"] = 2.0;
    EXPECT_DOUBLE_EQ(evaluate("x = x + 3"), 5.0);
    EXPECT_DOUBLE_EQ(table["x"], 5.0);
}

// 浮点数测试
TEST_F(ParserTest, FloatingPointOperations) {
    EXPECT_DOUBLE_EQ(evaluate("3.14159 + 2.71828"), 5.85987);
    EXPECT_DOUBLE_EQ(evaluate("1.5 * 2.5"), 3.75);
    EXPECT_DOUBLE_EQ(evaluate("10.0 / 3.0"), 10.0 / 3.0);
}

// 特殊浮点数边界值
TEST_F(ParserTest, FloatingPointEdgeCases) {
    EXPECT_DOUBLE_EQ(evaluate("0.0000001 * 1000000"), 0.1);
    EXPECT_DOUBLE_EQ(evaluate("1e-7 + 1e-7"), 2e-7);
}

// 复杂嵌套表达式
TEST_F(ParserTest, ComplexExpressions) {
    EXPECT_DOUBLE_EQ(evaluate("((1 + 2) * (3 + 4)) / (5 + 2)"), 3.0);
    EXPECT_DOUBLE_EQ(evaluate("1 + 2 * 3 + 4 * 5"), 27.0);
    EXPECT_DOUBLE_EQ(evaluate("(1 + 2) * 3 - 4 / 2"), 7.0);
}

// 多重变量赋值和引用
TEST_F(ParserTest, MultipleVariables) {
    EXPECT_NO_THROW({
        evaluate("x = 10");
        evaluate("y = x * 2");
        evaluate("z = x + y");
        EXPECT_DOUBLE_EQ(table["x"], 10.0);
        EXPECT_DOUBLE_EQ(table["y"], 20.0);
        EXPECT_DOUBLE_EQ(table["z"], 30.0);
    });
}

// 变量名边界测试
TEST_F(ParserTest, VariableNameEdgeCases) {
    EXPECT_NO_THROW({
        evaluate("a = 1");
        evaluate("A = 2");
        evaluate("z9 = 3");
        evaluate("_var = 4");
        EXPECT_DOUBLE_EQ(table["a"], 1.0);
        EXPECT_DOUBLE_EQ(table["A"], 2.0);
        EXPECT_DOUBLE_EQ(table["z9"], 3.0);
        EXPECT_DOUBLE_EQ(table["_var"], 4.0);
    });
}

// 异常边界测试
TEST_F(ParserTest, ErrorHandlingEdgeCases) {
    // 连续操作符
    EXPECT_THROW(evaluate("1 ++ 2"), SyntaxError);
    EXPECT_THROW(evaluate("1 +* 2"), SyntaxError);
    
    // 不完整表达式
    EXPECT_THROW(evaluate("(1 + 2"), SyntaxError);
    EXPECT_THROW(evaluate(")1 + 2("), SyntaxError);
    
    // 除零的边界情况
    EXPECT_THROW(evaluate("1 / (1 - 1)"), ZeroDivide);
    EXPECT_THROW(evaluate("1 / (0.1 - 0.1)"), ZeroDivide);
}

// 数值边界测试
TEST_F(ParserTest, NumericBoundaries) {
    const double EPSILON = 1e-12;

    // 大数运算
    EXPECT_NO_THROW({
        double result = evaluate("999999999 * 999999999");
        EXPECT_GT(result, 9.9e17);
    });
    
    // 小数运算
    EXPECT_NO_THROW({
        double result = evaluate("0.000000001 / 1000000000");
        EXPECT_NEAR(result, 1e-18, EPSILON);
    });
    
    // 精度边界测试
    EXPECT_NO_THROW({
        double result = evaluate("1e-15 * 1e-15");
        EXPECT_NEAR(result, 1e-30, EPSILON * 1e-18);
    });
}