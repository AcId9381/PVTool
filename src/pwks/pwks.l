%{/** C/C++ Declarations **/
    #include <iostream>
    #include <cstdlib>
    #include "pwks.scanner.hpp"
    #include "pwks.parser.hh"
    #include "pwks.driver.hpp"
    #include "location.hh"

    using namespace std;

    // Original yyterminate() macro returns int. Since we're using Bison 3 variants
    // as tokens, we must redefine it to change type from `int` to `Parser::semantic_type
    #define yyterminate() PVTool::PWKS::Parser::make_END(PVTool::PWKS::location());


	// This will track current scanner location.
	// Action is called when length of the token is known.
    #define YY_USER_ACTION m_driver.increaseLocation(yyleng);
%}

/** Flex Declarations and Options **/

/* Enable c++ scanner class generation */
%option c++

/* Change name of the scanner class. resulting name is "PWKSFlexLexer" */
%option prefix="PWKS"

/* Tell flex to use the sub-class "Scanner" instead of "PWKSFlexLexer" */
%option yyclass="Scanner"

/* Manual says "somewhat more optimized" */
%option batch

/* Make scanner abort with error on unmatched input */
%option nodefault

/** Make scanner behave as if 'yywrap()' returned 1 */
%option noyywrap


%% /** Regular expression part **/

[\(\{\[<] { /* LEFT PARENTHESES */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: LPAREN at " << PVTool::PWKS::location() << endl;
    #endif

    return PVTool::PWKS::Parser::make_LPAREN( PVTool::PWKS::location() );
}


[\)\}\]>] { /* RIGHT PARENTHESES */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: RPAREN at " << PVTool::PWKS::location() << endl;
    #endif

    return PVTool::PWKS::Parser::make_RPAREN( PVTool::PWKS::location() );
}

\+ { /* ADDITION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: ADD at " << PVTool::PWKS::location() << endl;
    #endif

    return PVTool::PWKS::Parser::make_ADD( PVTool::PWKS::location() );
}

[0-9]+ { /* INTEGER */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: INT '" << yytext << "' at " << PVTool::PWKS::location() << endl;
    #endif

    return PVTool::PWKS::Parser::make_INT(std::stoi(yytext), PVTool::PWKS::location());
}

[a-zA-Z._-]+[a-zA-Z0-9._-]* { /* STRING */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: STRING '" << yytext << "' at " << PVTool::PWKS::location() << endl;
    #endif

    return PVTool::PWKS::Parser::make_STRING(yytext, PVTool::PWKS::location());
}

= { /* EQUAL SIGN */

    /* EQUAL SIGN; IGNORED */
}

\* { /* ASTERISK */

    /* ASTERISK; IGNORED */
}


[ \t\r] { /* WHITESPACE */

    /* WHITESPACE CHAR; IGNORED */
}


(\r\n|\n) { /* NEWLINE */

    /* NEWLINE; IGNORED */
}


<<EOF>> { /* END OF FILE */

    return yyterminate();
}


. { /* UNMATHCED */

    cout << "Unrecognized symbol: " << yytext << endl;
}
