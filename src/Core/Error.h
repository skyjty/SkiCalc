#pragma once
#include <stdexcept>

class ZeroDivide : public std::runtime_error {
public:
    ZeroDivide() : std::runtime_error("attempt to divide by zero") {}
};

class SyntaxError : public std::runtime_error {
public:
    SyntaxError(const char* msg) : std::runtime_error(msg) {}
};