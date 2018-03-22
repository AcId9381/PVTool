// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 30 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:397

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

#line 49 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:397


// First part of user declarations.

#line 54 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "wctl.parser.hh"

// User implementation prologue.

#line 68 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 4 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:479
namespace PVTool { namespace WCTL {
#line 154 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:479

  /// Build a parser object.
  Parser::Parser (PVTool::WCTL::Scanner &scanner_yyarg, PVTool::WCTL::Driver &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 23: // pformula
        value.move< PathFormula* > (that.value);
        break;

      case 22: // sformula
        value.move< StateFormula* > (that.value);
        break;

      case 18: // "double"
      case 24: // bound
        value.move< double > (that.value);
        break;

      case 17: // "integer"
        value.move< int > (that.value);
        break;

      case 12: // "string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 23: // pformula
        value.copy< PathFormula* > (that.value);
        break;

      case 22: // sformula
        value.copy< StateFormula* > (that.value);
        break;

      case 18: // "double"
      case 24: // bound
        value.copy< double > (that.value);
        break;

      case 17: // "integer"
        value.copy< int > (that.value);
        break;

      case 12: // "string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 23: // pformula
        yylhs.value.build< PathFormula* > ();
        break;

      case 22: // sformula
        yylhs.value.build< StateFormula* > ();
        break;

      case 18: // "double"
      case 24: // bound
        yylhs.value.build< double > ();
        break;

      case 17: // "integer"
        yylhs.value.build< int > ();
        break;

      case 12: // "string"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 80 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        driver.formula(yystack_[0].value.as< StateFormula* > ());
    }
#line 557 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 87 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new True();
    }
#line 565 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 92 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > ()= new False();
    }
#line 573 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 97 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new Proposition(yystack_[0].value.as< std::string > ());
    }
#line 581 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 102 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new Negation(yystack_[0].value.as< StateFormula* > ());
    }
#line 589 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 107 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new Conjunction(yystack_[2].value.as< StateFormula* > (), yystack_[0].value.as< StateFormula* > ());
    }
#line 597 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 112 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new Disjunction(yystack_[2].value.as< StateFormula* > (), yystack_[0].value.as< StateFormula* > ());
    }
#line 605 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 117 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new Exists(yystack_[0].value.as< PathFormula* > ());
    }
#line 613 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 122 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = new Forall(yystack_[0].value.as< PathFormula* > ());
    }
#line 621 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 127 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< StateFormula* > () = yystack_[1].value.as< StateFormula* > ();
    }
#line 629 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 135 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< PathFormula* > () = new Next(yystack_[1].value.as< double > (), yystack_[0].value.as< StateFormula* > ());
    }
#line 637 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 140 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< PathFormula* > () = new Until(yystack_[1].value.as< double > (), yystack_[3].value.as< StateFormula* > (), yystack_[0].value.as< StateFormula* > ());
    }
#line 645 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 145 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< PathFormula* > () = yystack_[1].value.as< PathFormula* > ();
    }
#line 653 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 152 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< double > () = yystack_[1].value.as< double > ();
    }
#line 661 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 156 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:859
    {
        yylhs.value.as< double > () = (double)yystack_[1].value.as< int > ();
    }
#line 669 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
    break;


#line 673 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char Parser::yypact_ninf_ = -5;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      21,    -5,    -5,    21,     1,     1,    -5,    21,     2,    33,
      -5,     7,     1,    31,    -5,    -5,    29,    -5,    21,    21,
      10,    21,     9,     3,     7,    -5,    -5,    -5,    15,    25,
      -5,    -5,    21,    -5,    -5,    -5
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     3,     4,     0,     0,     0,     5,     0,     0,     2,
       6,     0,     0,     0,     9,    10,     0,     1,     0,     0,
       0,     0,     0,     0,     0,    11,     7,     8,     0,     0,
      12,    14,     0,    16,    15,    13
  };

  const signed char
  Parser::yypgoto_[] =
  {
      -5,    -5,     0,    -4,    20
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     8,    13,    14,    21
  };

  const unsigned char
  Parser::yytable_[] =
  {
       9,    15,    17,    10,     1,     2,     3,    16,    23,     4,
       5,    11,    22,     6,    12,    18,    19,    31,    26,    27,
      24,    30,    20,    25,     1,     2,     3,    28,    29,     4,
       5,    33,    35,     6,     7,    18,    19,    18,    19,    18,
      19,    34,    24,    25,    32
  };

  const unsigned char
  Parser::yycheck_[] =
  {
       0,     5,     0,     3,     3,     4,     5,     7,    12,     8,
       9,    10,    12,    12,    13,     6,     7,    14,    18,    19,
      11,    21,    15,    14,     3,     4,     5,    17,    18,     8,
       9,    16,    32,    12,    13,     6,     7,     6,     7,     6,
       7,    16,    11,    14,    24
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,     8,     9,    12,    13,    21,    22,
      22,    10,    13,    22,    23,    23,    22,     0,     6,     7,
      15,    24,    22,    23,    11,    14,    22,    22,    17,    18,
      22,    14,    24,    16,    16,    22
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    20,    21,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    23,    23,    23,    24,    24
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     2,     3,     3,     2,
       2,     3,     3,     4,     3,     3,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"true\"", "\"false\"",
  "\"negation\"", "\"conjunction\"", "\"disjunction\"",
  "\"existential quantification\"", "\"universal quantification\"",
  "\"next\"", "\"until\"", "\"string\"", "\"left parentheses\"",
  "\"right parentheses\"", "\"left bracket\"", "\"right bracket\"",
  "\"integer\"", "\"double\"", "\"addition\"", "$accept", "input",
  "sformula", "pformula", "bound", YY_NULLPTR
  };


  const unsigned char
  Parser::yyrline_[] =
  {
       0,    79,    79,    86,    91,    96,   101,   106,   111,   116,
     121,   126,   134,   139,   144,   151,   155
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 4 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:1167
} } // PVTool::WCTL
#line 972 "C:\\PVTool\\src\\wctl/wctl.parser.cc" // lalr1.cc:1167
#line 160 "C:\\PVTool\\src\\wctl\\wctl.y" // lalr1.cc:1168

// Bison expects us to provide implementation - otherwise linker complains
void PVTool::WCTL::Parser::error(const location &loc , const std::string &message) {

    // Location should be initialized inside scanner action, but is not in this example.
    // Let's grab location directly from driver class.
    cout << "Error: " << message << endl << "Location: " << loc << endl;

    //    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
