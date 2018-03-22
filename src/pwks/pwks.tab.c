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
#line 30 "pwks.y" // lalr1.cc:397

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

#line 49 "pwks.tab.c" // lalr1.cc:397


// First part of user declarations.

#line 54 "pwks.tab.c" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "pwks.tab.h"

// User implementation prologue.

#line 68 "pwks.tab.c" // lalr1.cc:412


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

#line 4 "pwks.y" // lalr1.cc:479
namespace PVTool { namespace PWKS {
#line 154 "pwks.tab.c" // lalr1.cc:479

  /// Build a parser object.
  Parser::Parser (PVTool::PWKS::Scanner &scanner_yyarg, PVTool::PWKS::Driver &driver_yyarg)
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
      case 17: // expr
        value.move< Model::Expression > (that.value);
        break;

      case 16: // term
        value.move< Model::Expression::term > (that.value);
        break;

      case 12: // state
        value.move< Model::State* > (that.value);
        break;

      case 5: // INT
      case 15: // prod
        value.move< int > (that.value);
        break;

      case 11: // slist
        value.move< std::list<Model::State>* > (that.value);
        break;

      case 13: // transitions
        value.move< std::list<Model::Transition>* > (that.value);
        break;

      case 14: // propositions
        value.move< std::list<std::string> > (that.value);
        break;

      case 6: // STRING
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
      case 17: // expr
        value.copy< Model::Expression > (that.value);
        break;

      case 16: // term
        value.copy< Model::Expression::term > (that.value);
        break;

      case 12: // state
        value.copy< Model::State* > (that.value);
        break;

      case 5: // INT
      case 15: // prod
        value.copy< int > (that.value);
        break;

      case 11: // slist
        value.copy< std::list<Model::State>* > (that.value);
        break;

      case 13: // transitions
        value.copy< std::list<Model::Transition>* > (that.value);
        break;

      case 14: // propositions
        value.copy< std::list<std::string> > (that.value);
        break;

      case 6: // STRING
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
      case 17: // expr
        yylhs.value.build< Model::Expression > ();
        break;

      case 16: // term
        yylhs.value.build< Model::Expression::term > ();
        break;

      case 12: // state
        yylhs.value.build< Model::State* > ();
        break;

      case 5: // INT
      case 15: // prod
        yylhs.value.build< int > ();
        break;

      case 11: // slist
        yylhs.value.build< std::list<Model::State>* > ();
        break;

      case 13: // transitions
        yylhs.value.build< std::list<Model::Transition>* > ();
        break;

      case 14: // propositions
        yylhs.value.build< std::list<std::string> > ();
        break;

      case 6: // STRING
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
#line 72 "pwks.y" // lalr1.cc:859
    {
        Model *m = new Model(*yystack_[0].value.as< std::list<Model::State>* > ());
        delete(yystack_[0].value.as< std::list<Model::State>* > ());
        cout << m->toString() << endl;
        driver.model(m);
    }
#line 596 "pwks.tab.c" // lalr1.cc:859
    break;

  case 3:
#line 81 "pwks.y" // lalr1.cc:859
    {
        std::list<Model::State> *lst = new std::list<Model::State>;
        lst->push_front(Model::State(*yystack_[0].value.as< Model::State* > ()));
        delete(yystack_[0].value.as< Model::State* > ());
        yylhs.value.as< std::list<Model::State>* > () = lst;
    }
#line 607 "pwks.tab.c" // lalr1.cc:859
    break;

  case 4:
#line 89 "pwks.y" // lalr1.cc:859
    {
        yystack_[0].value.as< std::list<Model::State>* > ()->push_front(Model::State(*yystack_[1].value.as< Model::State* > ()));
        delete(yystack_[1].value.as< Model::State* > ());
        yylhs.value.as< std::list<Model::State>* > () = yystack_[0].value.as< std::list<Model::State>* > ();
    }
#line 617 "pwks.tab.c" // lalr1.cc:859
    break;

  case 5:
#line 97 "pwks.y" // lalr1.cc:859
    {
        std::list<std::string> props;
        std::list<Model::Transition> trans;
        Model::State *s = new Model::State(yystack_[2].value.as< std::string > (), props, trans);
        yylhs.value.as< Model::State* > () = s;
    }
#line 628 "pwks.tab.c" // lalr1.cc:859
    break;

  case 6:
#line 105 "pwks.y" // lalr1.cc:859
    {
        std::list<Model::Transition> trans;
        Model::State *s = new Model::State(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::list<std::string> > (), trans);
        yylhs.value.as< Model::State* > () = s;
    }
#line 638 "pwks.tab.c" // lalr1.cc:859
    break;

  case 7:
#line 112 "pwks.y" // lalr1.cc:859
    {
        std::list<std::string> props;
        Model::State *s = new Model::State(yystack_[3].value.as< std::string > (), props, *yystack_[0].value.as< std::list<Model::Transition>* > ());
        delete(yystack_[0].value.as< std::list<Model::Transition>* > ());
        yylhs.value.as< Model::State* > () = s;
    }
#line 649 "pwks.tab.c" // lalr1.cc:859
    break;

  case 8:
#line 120 "pwks.y" // lalr1.cc:859
    {
        Model::State *s = new Model::State(yystack_[4].value.as< std::string > (), yystack_[2].value.as< std::list<std::string> > (), *yystack_[0].value.as< std::list<Model::Transition>* > ());
        delete(yystack_[0].value.as< std::list<Model::Transition>* > ());
        yylhs.value.as< Model::State* > () = s;
    }
#line 659 "pwks.tab.c" // lalr1.cc:859
    break;

  case 9:
#line 129 "pwks.y" // lalr1.cc:859
    {
        yystack_[2].value.as< Model::Expression > ().normalize();
        std::list<Model::Transition> *lst = new std::list<Model::Transition>();
        lst->push_front(Model::Transition(yystack_[2].value.as< Model::Expression > (), yystack_[0].value.as< std::string > ()));
        yylhs.value.as< std::list<Model::Transition>* > () = lst;
    }
#line 670 "pwks.tab.c" // lalr1.cc:859
    break;

  case 10:
#line 137 "pwks.y" // lalr1.cc:859
    {
        yystack_[3].value.as< Model::Expression > ().normalize();
        yystack_[0].value.as< std::list<Model::Transition>* > ()->push_front(Model::Transition(yystack_[3].value.as< Model::Expression > (),yystack_[1].value.as< std::string > ()));
        yylhs.value.as< std::list<Model::Transition>* > () = yystack_[0].value.as< std::list<Model::Transition>* > ();
    }
#line 680 "pwks.tab.c" // lalr1.cc:859
    break;

  case 11:
#line 145 "pwks.y" // lalr1.cc:859
    {
        std::list<std::string> lst;
        lst.push_front(yystack_[0].value.as< std::string > ());
        yylhs.value.as< std::list<std::string> > () = lst;
    }
#line 690 "pwks.tab.c" // lalr1.cc:859
    break;

  case 12:
#line 152 "pwks.y" // lalr1.cc:859
    {
        yystack_[0].value.as< std::list<std::string> > ().push_front(yystack_[1].value.as< std::string > ());
        yylhs.value.as< std::list<std::string> > () = yystack_[0].value.as< std::list<std::string> > ();
    }
#line 699 "pwks.tab.c" // lalr1.cc:859
    break;

  case 13:
#line 159 "pwks.y" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[0].value.as< int > ();
    }
#line 707 "pwks.tab.c" // lalr1.cc:859
    break;

  case 14:
#line 163 "pwks.y" // lalr1.cc:859
    {
        yylhs.value.as< int > () = yystack_[1].value.as< int > () * yystack_[0].value.as< int > ();
    }
#line 715 "pwks.tab.c" // lalr1.cc:859
    break;

  case 15:
#line 170 "pwks.y" // lalr1.cc:859
    {
        Model::Expression::term t;

        t.coefficient = 1;
        t.symbol = yystack_[0].value.as< std::string > ();

        yylhs.value.as< Model::Expression::term > () = t;
    }
#line 728 "pwks.tab.c" // lalr1.cc:859
    break;

  case 16:
#line 180 "pwks.y" // lalr1.cc:859
    {
        Model::Expression::term t;

        t.coefficient = yystack_[0].value.as< int > ();
        t.symbol = "";

        yylhs.value.as< Model::Expression::term > () = t;
    }
#line 741 "pwks.tab.c" // lalr1.cc:859
    break;

  case 17:
#line 190 "pwks.y" // lalr1.cc:859
    {
        Model::Expression::term t;

        t.coefficient = yystack_[1].value.as< int > ();
        t.symbol = yystack_[0].value.as< std::string > ();

        yylhs.value.as< Model::Expression::term > () = t;
    }
#line 754 "pwks.tab.c" // lalr1.cc:859
    break;

  case 18:
#line 200 "pwks.y" // lalr1.cc:859
    {
        Model::Expression::term t;

        t.coefficient = yystack_[0].value.as< int > ();
        t.symbol = yystack_[1].value.as< std::string > ();

        yylhs.value.as< Model::Expression::term > () = t;
    }
#line 767 "pwks.tab.c" // lalr1.cc:859
    break;

  case 19:
#line 210 "pwks.y" // lalr1.cc:859
    {
        Model::Expression::term t;

        t.coefficient = yystack_[2].value.as< int > () * yystack_[0].value.as< int > ();
        t.symbol = yystack_[1].value.as< std::string > ();

        yylhs.value.as< Model::Expression::term > () = t;
    }
#line 780 "pwks.tab.c" // lalr1.cc:859
    break;

  case 20:
#line 222 "pwks.y" // lalr1.cc:859
    {
        Model::Expression exp;
        exp.add(yystack_[0].value.as< Model::Expression::term > ());
        yylhs.value.as< Model::Expression > () = exp;
    }
#line 790 "pwks.tab.c" // lalr1.cc:859
    break;

  case 21:
#line 227 "pwks.y" // lalr1.cc:859
    {
        yystack_[0].value.as< Model::Expression > ().add(yystack_[2].value.as< Model::Expression::term > ());
        yylhs.value.as< Model::Expression > () = yystack_[0].value.as< Model::Expression > ();
    }
#line 799 "pwks.tab.c" // lalr1.cc:859
    break;


#line 803 "pwks.tab.c" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -15;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      -5,     4,     5,   -15,    -5,    -2,   -15,   -15,     3,     6,
       7,   -15,     2,   -15,     6,    11,    11,    12,     8,     9,
     -15,   -15,   -15,    11,     2,    13,   -15,   -15,     6,   -15
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     3,     0,     1,     4,    11,     5,
       0,    12,     0,     7,     6,    13,    15,    16,    20,     0,
       8,    14,    18,    17,     0,     0,    19,    21,     9,    10
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -15,   -15,    16,   -15,   -14,    14,   -13,   -15,    -3
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,    13,    10,    17,    18,    19
  };

  const unsigned char
  Parser::yytable_[] =
  {
      20,     1,    21,    22,     8,     6,     9,    15,    16,     8,
      26,     5,    24,    12,    29,    14,    15,    25,    23,    28,
       7,    27,    11
  };

  const unsigned char
  Parser::yycheck_[] =
  {
      14,     6,    15,    16,     6,     0,     8,     5,     6,     6,
      23,     7,     4,     7,    28,     8,     5,     8,     6,     6,
       4,    24,     8
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,    10,    11,    12,     7,     0,    11,     6,     8,
      14,    14,     7,    13,     8,     5,     6,    15,    16,    17,
      13,    15,    15,     6,     4,     8,    15,    17,     6,    13
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,     9,    10,    11,    11,    12,    12,    12,    12,    13,
      13,    14,    14,    15,    15,    16,    16,    16,    16,    16,
      17,    17
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     3,     4,     4,     5,     4,
       5,     1,     2,     1,     2,     1,     1,     2,     2,     3,
       1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "EQUALS", "ADD", "INT",
  "STRING", "LPAREN", "RPAREN", "$accept", "input", "slist", "state",
  "transitions", "propositions", "prod", "term", "expr", YY_NULLPTR
  };


  const unsigned char
  Parser::yyrline_[] =
  {
       0,    71,    71,    80,    88,    96,   104,   111,   119,   128,
     136,   144,   151,   158,   162,   169,   179,   189,   199,   209,
     221,   227
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


#line 4 "pwks.y" // lalr1.cc:1167
} } // PVTool::PWKS
#line 1094 "pwks.tab.c" // lalr1.cc:1167
#line 232 "pwks.y" // lalr1.cc:1168

// Bison expects us to provide implementation - otherwise linker complains
void PVTool::PWKS::Parser::error(const location &loc , const std::string &message) {

    // Location should be initialized inside scanner action, but is not in this example.
    // Let's grab location directly from driver class.
    cout << "Error: " << message << endl << "Location: " << loc << endl;

    //    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
