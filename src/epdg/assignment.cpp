#include <list>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <typeinfo>

#include "assignment.hpp"

using namespace PVTool;

/****** Assignment ******/
Assignment::~Assignment()
{
    //dtor
}

std::string Assignment::toString() const
{
    std::cout << "This should not happen!" << std::endl;
    return "";
}



/****** Infinity ******/

Infinity::~Infinity()
{
    //dtor
}

std::string Infinity::toString() const
{
    return "Infinity";
}



/****** Cover ******/

Cover::Cover(Assignment *succ, double cond)
    : successor_assignment(succ),
      cover_condition(cond)
{
    //ctor
}

Cover::~Cover()
{
    //dtor
}

std::string Cover::toString() const
{
    return successor_assignment->toString() + " <= " + std::to_string(cover_condition);
}



/****** Negation ******/

Negation::Negation(Assignment *succ)
    : successor_assignment(succ)
{
    //ctor
}

Negation::~Negation()
{
    //dtor
}

std::string Negation::toString() const
{
    return "NOT[" + successor_assignment->toString() + "]";
}



/****** Expression ******/

Expression::Expression(const std::unordered_map<unsigned,std::string> *symb)
    : EPDG::Expression(symb)
{
    //ctor
}

Expression::Expression(const EPDG::Expression &exp)
    : EPDG::Expression(exp)
{
    //ctor
}

Expression::~Expression()
{
    //dtor
}

std::string Expression::toString() const
{
    return ((EPDG::Expression*)this)->toString();
}



/****** Plus ******/

Plus::Plus(const Expression wgt, const Assignment *ass)
    : weight(wgt),
      assignment(ass)
{
    //ctor
}

Plus::~Plus()
{
    //dtor
}

std::string Plus::toString() const
{
    return weight.toString() + " + " + assignment->toString();
}



/****** Max ******/

Max::Max(std::list<Assignment*> ops)
{
    operands = ops;
}

Max::~Max()
{
    //dtor
}

std::string Max::toString() const
{
    std::ostringstream strs;
    bool first = true;

    strs << "PVMAX[";

    for(Assignment *a : operands)
    {
        if(!first)
            strs << ", ";
        strs << a->toString();

        first = false;
    }

    strs << "]";

    return strs.str();
}



/****** Min ******/

Min::Min(std::list<Assignment*> ops)
{
    operands = ops;
}

Min::~Min()
{
    //dtor
}

std::string Min::toString() const
{
    std::ostringstream strs;
    bool first = true;

    strs << "PVMIN[";

    for(Assignment *a : operands)
    {
        if(!first)
            strs << ", ";
        strs << a->toString();

        first = false;
    }

    strs << "]";

    return strs.str();
}
