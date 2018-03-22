#include <sstream>
#include <iostream>
#include "wctl.driver.hpp"

using namespace PVTool::WCTL;

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

void Driver::formula(StateFormula *form)
{
    parsed_formula = form;
}

StateFormula* Driver::formula()
{
    return parsed_formula;
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
