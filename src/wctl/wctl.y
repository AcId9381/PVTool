%skeleton "lalr1.cc"
%require "3.0"
%defines
%define api.namespace {PVTool::WCTL}
%define parser_class_name {Parser}

%define api.token.constructor
%define api.value.type variant

%code requires
{
    #include "wctl.hpp"

    using namespace std;

    namespace PVTool {
        namespace WCTL {
            class Scanner;
            class Driver;
        }
    }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the scanner. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
    #include "wctl.hpp"
    #include "wctl.scanner.hpp"
    #include "wctl.parser.hh"
    #include "wctl.driver.hpp"
    #include "location.hh"

    // yylex() arguments are defined in wctl.y
    static PVTool::WCTL::Parser::symbol_type yylex(PVTool::WCTL::Scanner &scanner, PVTool::WCTL::Driver &driver) {
        return scanner.get_next_token();
    }

    using namespace PVTool::WCTL;
}

%lex-param {PVTool::WCTL::Scanner &scanner}
%lex-param {PVTool::WCTL::Driver &driver}
%parse-param  {PVTool::WCTL::Scanner &scanner}
%parse-param {PVTool::WCTL::Driver &driver}

%locations

%token END 0 "end of file"
%token TRUE "true"
%token FALSE "false"
%token NEG "negation"
%token AND "conjunction"
%token OR "disjunction"
%token EXISTS "existential quantification"
%token FORALL "universal quantification"
%token NEXT "next"
%token UNTIL "until"
%token <std::string> STRING "string"
%token LPAREN "left parentheses"
%token RPAREN "right parentheses"
%token LBRACK "left bracket"
%token RBRACK "right bracket"
%token <int> INT "integer"
%token <double> DOUBLE "double"
%token ADD "addition"

%type <StateFormula*> sformula
%type <PathFormula*> pformula
%type <double> bound

%left AND OR NEG NEXT UNTIL ADD

%%
input:
    sformula
    {
        driver.formula($1);
    }


sformula:
    TRUE
    {
        $$ = new True();
    }

    | FALSE
    {
        $$= new False();
    }

    | STRING
    {
        $$ = new Proposition($1);
    }

    | NEG sformula
    {
        $$ = new Negation($2);
    }

    | sformula AND sformula
    {
        $$ = new Conjunction($1, $3);
    }

    | sformula OR sformula
    {
        $$ = new Disjunction($1, $3);
    }

    | EXISTS pformula
    {
        $$ = new Exists($2);
    }

    | FORALL pformula
    {
        $$ = new Forall($2);
    }

    | LPAREN sformula RPAREN
    {
        $$ = $2;
    }



pformula:
    NEXT bound sformula
    {
        $$ = new Next($2, $3);
    }

    | sformula UNTIL bound sformula
    {
        $$ = new Until($3, $1, $4);
    }

    | LPAREN pformula RPAREN
    {
        $$ = $2;
    }


bound:
    LBRACK DOUBLE RBRACK
    {
        $$ = $2;
    }
    | LBRACK INT RBRACK
    {
        $$ = (double)$2;
    }

%%
// Bison expects us to provide implementation - otherwise linker complains
void PVTool::WCTL::Parser::error(const location &loc , const std::string &message) {

    // Location should be initialized inside scanner action, but is not in this example.
    // Let's grab location directly from driver class.
    cout << "Error: " << message << endl << "Location: " << loc << endl;

    //    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
