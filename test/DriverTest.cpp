#include "DriverTest.h"

// 基本算术运算测试
TEST_F(DriverTest, EvaluateSimpleExpression) {
    runWithInput("3 + 4\n");
    EXPECT_EQ(out.str(), "7\n");
}

// 多行输入和变量赋值测试
TEST_F(DriverTest, EvaluateMultipleLines) {
    runWithInput("2 * 5\nx = 3\nx + 1\n");
    EXPECT_EQ(out.str(), "10\n3\n4\n");
}

// 除零错误处理测试
TEST_F(DriverTest, DivisionByZeroError) {
    runWithInput("5 / 0\n");
    EXPECT_EQ(err.str(), "attempt to divide by zero\n");
    EXPECT_EQ(driver.errorCount, 1);
}

// 语法错误处理测试
TEST_F(DriverTest, SyntaxErrorHandling) {
    runWithInput("3 + * 4\n");
    EXPECT_TRUE(err.str().find("syntax error") != std::string::npos);
    EXPECT_EQ(driver.errorCount, 1);
}

// 内置常量测试
TEST_F(DriverTest, BuiltInConstants) {
    runWithInput("pi\ne\n");
    std::stringstream expected;
    expected << 3.1415926535 << '\n' << 2.718 << '\n';
    EXPECT_EQ(out.str(), expected.str());
}

// 复杂表达式测试
TEST_F(DriverTest, ComplexExpression) {
    runWithInput("x = 2\ny = 3\n(x + y) * (x - y)\n");
    EXPECT_EQ(out.str(), "2\n3\n-5\n");
}

// 空行和空白处理测试
TEST_F(DriverTest, HandleEmptyLines) {
    runWithInput("\n  \n\t\n3\n");
    EXPECT_EQ(out.str(), "3\n");
}
