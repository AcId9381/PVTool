#ifndef PWKS_SCANNER_HPP_INCLUDED
#define PWKS_SCANNER_HPP_INCLUDED

/**
 * Generated Flex class name is yyFlexLexer by default. If we want to use more flex-generated
 * classes we should name them differently. See scanner.l prefix option.
 *
 * Unfortunately the implementation relies on this trick with redefining class name
 * with a preprocessor macro. See GNU Flex manual, "Generating C++ Scanners" section
**/
#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer PWKSFlexLexer
#include <FlexLexer.h>
#endif // ! defined(yyFlexLexerOnce)

/**
* Scanner method signature is defined by this macro. Original yylex() returns int.
* Sinice Bison 3 uses symbol_type, we must change returned type. We also rename it
* to something sane, since you cannot overload return type.
**/
#undef YY_DECL
#define YY_DECL PVTool::PWKS::Parser::symbol_type PVTool::PWKS::Scanner::get_next_token()

#include "pwks.parser.hh"

namespace PVTool::PWKS
{

    // Forward declare interpreter to avoid include. Header is added in implementation file.
    class Driver;

    class Scanner : public yyFlexLexer
    {
        public:
            Scanner(Driver &driver) : m_driver(driver) {}
            virtual ~Scanner() {}
            virtual PVTool::PWKS::Parser::symbol_type get_next_token();

        private:
            Driver &m_driver;
    };
}

#endif // PWKS_SCANNER_HPP_INCLUDED
