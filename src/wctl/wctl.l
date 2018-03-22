%{/** C/C++ Declarations **/
    #include <iostream>
    #include <cstdlib>
    #include "wctl.scanner.hpp"
    #include "wctl.parser.hh"
    #include "wctl.driver.hpp"
    #include "location.hh"

    using namespace std;

    // Original yyterminate() macro returns int. Since we're using Bison 3 variants
    // as tokens, we must redefine it to change type from `int` to `Parser::semantic_type
    #define yyterminate() PVTool::WCTL::Parser::make_END(PVTool::WCTL::location());


	// This will track current scanner location.
	// Action is called when length of the token is known.
    #define YY_USER_ACTION m_driver.increaseLocation(yyleng);
%}

/** Flex Declarations and Options **/

/* Enable c++ scanner class generation */
%option c++

/* Change name of the scanner class. resulting name is "WCTLFlexLexer" */
%option prefix="WCTL"

/* Tell flex to use the sub-class "Scanner" instead of "LogicFlexLexer" */
%option yyclass="Scanner"

/* Manual says "somewhat more optimized" */
%option batch

/* Make scanner abort with error on unmatched input */
%option nodefault

/** Make scanner behave as if 'yywrap()' returned 1 */
%option noyywrap


%% /** Regular expression part **/

[tT][rR][uU][eE] { /* TRUE */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: TRUE at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_TRUE( PVTool::WCTL::location() );
}

[fF][aA][lL][sS][eE] { /* FALSE */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: FALSE at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_FALSE( PVTool::WCTL::location() );
}

[nN][oO][tT] { /* NEGATION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: NEG at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_NEG( PVTool::WCTL::location() );
}


&& { /* CONJUNCTION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: AND at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_AND( PVTool::WCTL::location() );
}


\|\| { /* DISJUNCTION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: OR at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_OR( PVTool::WCTL::location() );
}


E { /* EXISTENTIAL QUANTIFICATION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: EXISTS at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_EXISTS( PVTool::WCTL::location() );
}


A { /* UNIVERSAL QUANTIFICATION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: FORALL at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_FORALL( PVTool::WCTL::location() );
}


X { /* NEXT */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: NEXT at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_NEXT( PVTool::WCTL::location() );
}


U { /* UNTIL */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: UNTIL at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_UNTIL( PVTool::WCTL::location() );
}


[\(\{] { /* LEFT PARENTHESES */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: LPAREN at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_LPAREN( PVTool::WCTL::location() );
}


[\)\}] { /* RIGHT PARENTHESES */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: RPAREN at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_RPAREN( PVTool::WCTL::location() );
}


\[ { /* LEFT BRACKET */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: LBRACK at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_LBRACK( PVTool::WCTL::location() );
}


\] { /* RIGHT BRACKET */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: RBRACK at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_RBRACK( PVTool::WCTL::location() );
}


\+ { /* ADDITION */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: ADD at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_ADD( PVTool::WCTL::location() );
}

[0-9]+ { /* INTEGER */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: INT '" << yytext << "' at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_INT(std::stoi(yytext), PVTool::WCTL::location());
}


[0-9]+"."[0-9]* { /* DOUBLE */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: DOBULE '" << yytext << "' at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_DOUBLE(std::stod(yytext), PVTool::WCTL::location());
}


[a-zB-DF-TVYZ._-]+[a-zB-DF-TVYZ0-9._-]* { /* STRING */

    #if defined(FLEX_DEBUG)
    cout << "Scanner: STRING '" << yytext << "' at " << PVTool::WCTL::location() << endl;
    #endif

    return PVTool::WCTL::Parser::make_STRING(yytext, PVTool::WCTL::location());
}


\* { /* ASTERISK */

    /* ASTERISK; IGNORED */
}

, { /* COMMA */
    /* COMMA; IGNORED */

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
