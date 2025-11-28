#include "Driver.h"

#include <iostream>
#include <memory>
#include "Lexer.h"
#include "Parser.h"
#include "Error.h"


void Driver::run(std::istream& in) {
    std::map<std::string, double> table = {
        {"pi", 3.1415926535},
        {"e", 2.718}
    };

    Lexer lexer;
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::istringstream input(line);
        Parser parser(lexer, input, table);

        try {
            lexer.getToken(input);
            if (lexer.currToken == TokenType::END) continue;
            
            double result = parser.expr(false);
            std::cout << result << '\n';
        }
        catch (ZeroDivide&) {
            std::cerr << "attempt to divide by zero\n";
            ++errorCount;
        }
        catch (SyntaxError& e) {
            std::cerr << "syntax error: " << e.what() << '\n';
            ++errorCount;
        }
    }
}