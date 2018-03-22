#ifndef PWKS_DRIVER_HPP_INCLUDED
#define PWKS_DRIVER_HPP_INCLUDED

#include "pwks.scanner.hpp"
#include "pwks.parser.hh"
#include <string>
#include <iostream>

namespace PVTool::PWKS
{
    class Driver
    {
        public:
            Driver();
            ~Driver();
            int parse();
            int parse(std::string input);
            int parse(std::ifstream *input);
            void model(Model *model);
            Model *model();
            void switchInputStream(std::istream *is);

            friend class Parser;
            friend class Scanner;

        private:
            void increaseLocation(unsigned int loc);
            unsigned int location() const;

            Model *parsed_model;
            Scanner m_scanner;
            Parser m_parser;
            unsigned int m_location; // Used by scanner
    };
}

#endif // PWKS_DRIVER_HPP_INCLUDED
