#include <iostream>
#include "pwks.hpp"
#include "pwks.driver.hpp"
#include "pwks.parser.hh"

int main(int argc, char *argv[])
{
    PVTool::PWKS::Driver driver;

    driver.parse(argv[1]);

    std::cout << driver.model()->toDot() << std::endl;

    return 0;
}
