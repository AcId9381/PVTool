%skeleton "lalr1.cc"
%require "3.0"
%defines
%define api.namespace {PVTool::PWKS}
%define parser_class_name {Parser}

%define api.token.constructor
%define api.value.type variant

%code requires
{
    #include "pwks.hpp";

    using namespace std;

    namespace PVTool {
        namespace PWKS {
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
    #include "pwks.hpp"
    #include "pwks.scanner.hpp"
    #include "pwks.parser.hh"
    #include "pwks.driver.hpp"
    #include "location.hh"

    // yylex() arguments are defined in pwks.y
    static PVTool::PWKS::Parser::symbol_type yylex(PVTool::PWKS::Scanner &scanner, PVTool::PWKS::Driver &driver) {
        return scanner.get_next_token();
    }

    using namespace PVTool::PWKS;
}

%lex-param {PVTool::PWKS::Scanner &scanner}
%lex-param {PVTool::PWKS::Driver &driver}
%parse-param  {PVTool::PWKS::Scanner &scanner}
%parse-param {PVTool::PWKS::Driver &driver}

%locations

%token END 0 "end of file"
%token EQUALS
%token ADD
%token <int> INT
%token <std::string> STRING
%token LPAREN
%token RPAREN

%type <int> prod
%type <Model::Expression::term> term
%type <Model::Expression> expr
%type <std::list<std::string>> propositions
%type <std::list<Model::Transition>*> transitions
%type <Model::State*> state
%type <std::list<Model::State>*> slist

%%

input:
    slist
    {
        Model *m = new Model(*$1);
        delete($1);
        driver.model(m);
    }

slist:
    state
    {
        std::list<Model::State> *lst = new std::list<Model::State>;
        lst->push_front(Model::State(*$1));
        delete($1);
        $$ = lst;
    }

    | state slist
    {
        $2->push_front(Model::State(*$1));
        delete($1);
        $$ = $2;
    }

state:
    STRING LPAREN RPAREN
    {
        std::list<std::string> props;
        std::list<Model::Transition> trans;
        Model::State *s = new Model::State($1, props, trans);
        $$ = s;
    }

    | STRING LPAREN propositions RPAREN
    {
        std::list<Model::Transition> trans;
        Model::State *s = new Model::State($1, $3, trans);
        $$ = s;
    }

    | STRING LPAREN RPAREN transitions
    {
        std::list<std::string> props;
        Model::State *s = new Model::State($1, props, *$4);
        delete($4);
        $$ = s;
    }

    | STRING LPAREN propositions RPAREN transitions
    {
        Model::State *s = new Model::State($1, $3, *$5);
        delete($5);
        $$ = s;
    }


transitions:
    LPAREN expr RPAREN STRING
    {
        $2.normalize();
        std::list<Model::Transition> *lst = new std::list<Model::Transition>();
        lst->push_front(Model::Transition($2, $4));
        $$ = lst;
    }

    | LPAREN expr RPAREN STRING transitions
    {
        $2.normalize();
        $5->push_front(Model::Transition($2,$4));
        $$ = $5;
    }

propositions:
    STRING
    {
        std::list<std::string> lst;
        lst.push_front($1);
        $$ = lst;
    }

    | STRING propositions
    {
        $2.push_front($1);
        $$ = $2;
    }

prod:
    INT
    {
        $$ = $1;
    }
    | INT prod
    {
        $$ = $1 * $2;
    }


term:
    STRING
    {
        Model::Expression::term t;

        t.coefficient = 1;
        t.symbol = $1;

        $$ = t;
    }

    | prod
    {
        Model::Expression::term t;

        t.coefficient = $1;
        t.symbol = "";

        $$ = t;
    }

    | prod STRING
    {
        Model::Expression::term t;

        t.coefficient = $1;
        t.symbol = $2;

        $$ = t;
    }

    | STRING prod
    {
        Model::Expression::term t;

        t.coefficient = $2;
        t.symbol = $1;

        $$ = t;
    }

    | prod STRING prod
    {
        Model::Expression::term t;

        t.coefficient = $1 * $3;
        t.symbol = $2;

        $$ = t;
    }


expr:
    term
    {
        Model::Expression exp;
        exp.add($1);
        $$ = exp;
    }
    | term ADD expr {
        $3.add($1);
        $$ = $3;
    }

%%
// Bison expects us to provide implementation - otherwise linker complains
void PVTool::PWKS::Parser::error(const location &loc , const std::string &message) {

    // Location should be initialized inside scanner action, but is not in this example.
    // Let's grab location directly from driver class.
    cout << "Error: " << message << endl << "Location: " << loc << endl;

    //    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
