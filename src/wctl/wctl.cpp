#include "wctl.hpp"
#include <string>
#include <sstream>

using namespace PVTool::WCTL;

/****** Formula ******/
Formula::~Formula()
{
    //dtor
}

std::string Formula::toString() const
{
    return "";
}

std::string Formula::toWKString() const
{
    return "";
}


/****** StateFormula ******/
StateFormula::~StateFormula()
{
    //dtor
}



/****** PathFormula ******/
PathFormula::PathFormula()
    : PathFormula(-1.0)
{
    //ctor
}

PathFormula::PathFormula(const double bnd)
    : bound(bnd)
{
    //ctor
}

PathFormula::~PathFormula()
{
    //dtor
}



/****** True ******/
True::True()
{
    //ctor
}

True::~True()
{
    //dtor
}

std::string True::toString() const
{
    return "TRUE";
}

std::string True::toWKString() const
{
    return toString();
}



/****** False ******/
False::False()
{
    //ctor
}

False::~False()
{
    //dtor
}

std::string False::toString() const
{
    return "FALSE";
}

std::string False::toWKString() const
{
    return toString();
}



/****** Proposition ******/
Proposition::Proposition(std::string prop)
    : proposition(prop)
{
    //ctor
}

Proposition::~Proposition()
{
    //dtor
}

std::string Proposition::toString() const
{
    return proposition;
}

std::string Proposition::toWKString() const
{
    return toString();
}



/****** Negation ******/
Negation::Negation(const StateFormula *form)
    : formula(form)
{
    //ctor
}

Negation::Negation(const Negation &obj)
    : Negation(obj.formula)
{
    //ctor
}

Negation::~Negation()
{
    delete(formula);
}

std::string Negation::toString() const
{
    return "!" + formula->toString();
}

std::string Negation::toWKString() const
{
    return toString();
}



/****** Conjunction ******/
Conjunction::Conjunction(const StateFormula *l, const StateFormula *r)
    : left(l),
      right(r)
{
    //ctor
}

Conjunction::Conjunction(const Conjunction &obj)
    : Conjunction(obj.left, obj.right)
{
    //ctor
}

Conjunction::~Conjunction()
{
    delete(left);
    delete(right);
}

std::string Conjunction::toString() const
{
    return "(" + left->toString() + " AND " + right->toString() + ")";
}

std::string Conjunction::toWKString() const
{
    return "(" + left->toWKString() + " && " + right->toWKString() + ")";
}



/****** Disjunction ******/
Disjunction::Disjunction(const StateFormula *l, const StateFormula *r)
    : left(l),
      right(r)
{
    //ctor
}

Disjunction::Disjunction(const Disjunction &obj)
    : Disjunction(obj.left, obj.right)
{
    //ctor
}

Disjunction::~Disjunction()
{
    delete(left);
    delete(right);
}

std::string Disjunction::toString() const
{
    return "(" + left->toString() + " OR " + right->toString() + ")";
}

std::string Disjunction::toWKString() const
{
    return "(" + left->toWKString() + " || " + right->toWKString() + ")";
}



/****** Exist ******/
Exists::Exists(const PathFormula *form)
    : formula(form)
{
    //ctor
}

Exists::Exists(const Exists &obj)
    : Exists(obj.formula)
{
    //ctor
}

Exists::~Exists()
{
    delete(formula);
}

std::string Exists::toString() const
{
    return "E" + formula->toString();
}

std::string Exists::toWKString() const
{
    return "E" + formula->toWKString();
}



/****** Forall ******/
Forall::Forall(const PathFormula *form)
    : formula(form)
{
    //ctor
}

Forall::Forall(const Forall &obj)
    : Forall(obj.formula)
{
    //ctor
}

Forall::~Forall()
{
    delete(formula);
}

std::string Forall::toString() const
{
    return "A" + formula->toString();
}

std::string Forall::toWKString() const
{
    return "A" + formula->toWKString();
}



/****** Next ******/
Next::Next(const double bound, const StateFormula *form)
    : PathFormula(bound),
      formula(form)
{
    //ctor
}

Next::Next(const Next &obj)
    : Next(obj.bound, obj.formula)
{
    //ctor
}

Next::~Next()
{
    delete(formula);
}

std::string Next::toString() const
{
    std::ostringstream sstr;
    sstr << "X";

    if(bound >= 0)
        sstr << "[" << bound << "]";

    sstr << "(" << formula->toString() << ")";

    return sstr.str();
}

std::string Next::toWKString() const
{
    std::ostringstream sstr;
    sstr << std::fixed;
    sstr << "X";

    if(bound >= 0)
        sstr << "[<=" << (int)bound << "]";

    sstr << "(" << formula->toWKString() << ")";

    return sstr.str();
}



/****** Until ******/
Until::Until(const double bnd, const StateFormula* l, const StateFormula *r)
    : PathFormula(bnd),
      left(l),
      right(r)
{
    //ctor
}

Until::Until(const Until &obj)
    : Until(obj.bound, obj.left, obj.right)
{
    //ctor
}

Until::~Until()
{
    delete(left);
    delete(right);
}

std::string Until::toString() const
{
    std::ostringstream sstr;

    sstr << "(" << left->toString() << ")" << "U";

    if(bound >= 0)
        sstr << "[" << bound << "]";

    sstr << "(" << right->toString() << ")";

    return sstr.str();
}

std::string Until::toWKString() const
{
    std::ostringstream sstr;

    sstr << std::fixed;

    sstr << "(" << left->toWKString() << ")" << "U";

    if(bound >= 0)
        sstr << "[<=" << (int)bound << "]";

    sstr << "(" << right->toWKString() << ")";

    return sstr.str();
}
