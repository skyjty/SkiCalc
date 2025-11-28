#include "Driver.h"
#include <iostream>

int main() {
    Driver driver;
    driver.run(std::cin);
    return driver.errorCount;
}