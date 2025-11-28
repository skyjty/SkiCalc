#pragma once
#include <iostream>
#include <sstream>
#include <memory>

#include "Lexer.h"
#include "Parser.h"
#include "Error.h"

class Driver {
public:
    int errorCount = 0;

    void run(std::istream& in);
};