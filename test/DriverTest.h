#pragma once

#include <gtest/gtest.h>
#include "Driver.h"

class DriverTest : public ::testing::Test {
protected:
    Driver driver;
    std::ostringstream out;
    std::ostringstream err;

    void runWithInput(const std::string& inputText) {
        std::istringstream in(inputText);
        // 重定向标准输出和错误输出
        std::streambuf* oldOut = std::cout.rdbuf(out.rdbuf());
        std::streambuf* oldErr = std::cerr.rdbuf(err.rdbuf());

        driver.run(in);

        // 恢复输出流
        std::cout.rdbuf(oldOut);
        std::cerr.rdbuf(oldErr);
    }
};
