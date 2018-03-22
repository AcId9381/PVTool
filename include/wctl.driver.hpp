#ifndef WCTL_DRIVER_HPP_INCLUDED
#define WCTL_DRIVER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include "wctl.scanner.hpp"
#include "wctl.parser.hh"
#include "wctl.hpp"

namespace PVTool::WCTL
{
    class Driver
    {
    public:
        Driver();
        virtual ~Driver();
        int parse();
        int parse(std::string input);
        int parse(std::ifstream *input);
        void switchInputStream(std::istream *is);
        void formula(StateFormula *form);
        StateFormula *formula();

        friend class Parser;
        friend class Scanner;

    private:
        void increaseLocation(unsigned int loc);
        unsigned int location() const;
        StateFormula *parsed_formula;

        Scanner m_scanner;
        Parser m_parser;
        unsigned int m_location; // Used by scanner
    };
}


#endif // WCTL_DRIVER_HPP_INCLUDED
