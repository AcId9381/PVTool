#include "pwks.driver.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace PVTool::PWKS;

Driver::Driver() :
    m_scanner(*this),
    m_parser(m_scanner, *this),
    m_location(0)
    {
        //ctor
    }

Driver::~Driver()
{
    //dtor
}

int Driver::parse()
{
    m_location = 0;
    return m_parser.parse();
}

int Driver::parse(std::string input)
{
    std::istringstream iss(input);
    switchInputStream(&iss);
    return parse();
}

int Driver::parse(std::ifstream *input)
{
    switchInputStream(input);
    return parse();
}

void Driver::model(Model *model)
{
    parsed_model = model;
}

Model *Driver::model()
{
    return parsed_model;
}

void Driver::switchInputStream(std::istream *is)
{
    m_scanner.switch_streams(is, NULL);
}

void Driver::increaseLocation(unsigned int loc)
{
    m_location += loc;
}

unsigned int Driver::location() const
{
    return m_location;
}
