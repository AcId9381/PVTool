#include "wctl.hpp"
#include "wctl.driver.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    PVTool::WCTL::Driver driver;
    driver.parse(argv[1]);
    std::cout << driver.formula()->toWKString();

    return 0;
}
