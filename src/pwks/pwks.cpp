#include <list>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>

#include "pwks.hpp"

using namespace PVTool::PWKS;

/****** term ******/

bool Model::Expression::term::compare(const term &first,
                                            const term &second)
{
    if(first.symbol == "")
        return false;
    else
        return first.symbol < second.symbol;
}



/****** Expression ******/

Model::Expression::Expression()
{
    //ctor
}

Model::Expression::Expression(term t)
{
    terms.push_back(t);
}

Model::Expression::Expression(std::list<term> tl)
{
    terms = tl;
    normalize();
}

Model::Expression::~Expression()
{
    //dtor
}

void Model::Expression::add(term t)
{
    terms.push_back(t);
    normalize();
}

void Model::Expression::normalize()
{
    for(auto it = std::begin(terms); it != std::end(terms); it++)
    {
        for(auto i = next(it,1); i != end(terms); )
        {
            if(it->symbol == i->symbol)
            {
                it->coefficient += i->coefficient;
                i = terms.erase(i);
            }
            else
                i++;
        }
    }

    terms.sort(term::compare);
}

std::set<std::string> Model::Expression::symbols() const
{
    std::set<std::string> res;

    for(term t : terms)
    {
        res.insert(t.symbol);
    }

    return res;
}

std::string Model::Expression::toString() const
{
    std::ostringstream strs;

    strs << std::fixed;

    // Used to keep track of how many terms we have added to the string
    unsigned i = 0U;

    for(auto it = std::begin(terms); it != std::end(terms); it++)
    {
        // Skip terms with a zero coefficient
        if(it->coefficient == 0U)
            continue;

        // If not first term, add '+' symbol
        if(i)
            strs << " + ";

        // Ignore coefficient of 1 for terms that have a non-empty symbol
        if(it->coefficient != 1U || it->symbol == "")
            strs << it->coefficient;

        strs << it->symbol;
        i++;
    }

    return strs.str();
}



/****** Transition ******/

Model::Transition::Transition(Expression wgt, std::string tgt)
    : weight(wgt),
      target(tgt)
{
    //ctor
}

Model::Transition::~Transition()
{
    //dtor
}

std::string Model::Transition::toString() const
{
    return "<" + weight.toString() + ">" + target;
}



/****** State ******/

Model::State::State(std::string sid, std::list<std::string> props,
                   std::list<Transition> trans)
    : identifier(sid),
      propositions(props),
      transitions(trans)
{
    //ctor
}

Model::State::~State()
{
    //dtor
}

bool Model::State::has_prop(std::string prop) const
{
    auto it = std::find(std::begin(propositions), std::end(propositions),
                        prop);

    return it != std::end(propositions);
}

std::string Model::State::toString() const
{
    std::ostringstream strs;

    // Add identifier
    strs << identifier << " = ";

    // Add propositions
    strs << "{";
    for(auto it = std::begin(propositions); it != std::end(propositions);
            it++)
    {
        if(it != std::begin(propositions))
            strs << ", ";
        strs << *it;
    }
    strs << "}";

    // Add transitions
    for(Transition t : transitions)
        strs << " " << t.toString();

    return strs.str();
}



/****** Model ******/

Model::Model(std::list<State> slist)
{
    if(!insert(slist))
    {
        std::cerr << "Could not insert states. Leaving state map empty."
                  << std::endl;
        states.clear();
    }
}

Model::Model()
{
    //ctor
}

Model::~Model()
{
    //dtor
}

bool Model::insert(State s)
{
    return insert(s, true);
}

bool Model::insert(std::list<State> slist)
{
    bool result = true;
    for(State s : slist)
    {
        if(!insert(s, false))
            result = false;
    }

    if(!verify_transitions(slist))
        result = false;

    return result;
}

bool Model::insert(State s, bool verify)
{
    bool result = true;
    if(!states.insert({s.identifier, s}).second)
    {
        std::cerr << "Could not insert state with identifier: '"
                  << s.identifier << "'. Perhaps identifier is a duplicate."
                  << std::endl;
        result = false;
    }

    if(!result)
        return result;

    if(verify)
        result = verify_transitions(s);

    return result;
}

bool Model::contains(std::string sid) const
{
    if(states.count(sid))
        return true;
    else
        return false;
}

Model::State *Model::get(std::string sid)
{
    auto ele = states.find(sid);

    if(ele != std::end(states))
        return &(ele->second);
    else
        return nullptr;
}

bool Model::verify_transitions(State s) const
{
    bool result = true;
    for(Transition t : s.transitions)
    {
        if(!states.count(t.target))
        {
            std::cerr << "Transition: '" << t.toString()
                      << "' has an invalid target." << std::endl;
            result = false;
        }
    }
    return result;
}

bool Model::verify_transitions(std::list<State> slist) const
{
    bool result = true;
    for(State s : slist)
    {
        if(!verify_transitions(s))
            result = false;
    }
    return result;
}

std::set<std::string> Model::symbols() const
{
    std::set<std::string> res;

    for(auto it : states)
    {
        State s = it.second;

        for(Transition trans : s.transitions)
        {
            res.merge(trans.weight.symbols());
        }
    }

    res.insert("");

    return res;
}

std::string Model::toString() const
{
    std::ostringstream strs;

    strs << "Model: " << std::endl;

    if(states.empty())
        return strs.str();



    for(auto it = std::begin(states); it != std::end(states); it++)
    {
        strs << "\t" << it->second.toString() << std::endl;
    }

    return strs.str();
}

std::string Model::toDot() const
{
    std::ostringstream strs;
    bool first = true;

    strs << "digraph {";

    for(auto it = std::begin(states); it != std::end(states); it++)
    {
        strs << (*it).second.identifier
             << "[label=\""
             << (*it).second.identifier
             << " {";

        for(auto itt = std::begin((*it).second.propositions); itt != std::end((*it).second.propositions); itt++)
        {
            if(itt != std::begin((*it).second.propositions))
                strs << ", ";
            strs << *itt;
        }

        strs << "}\"];";
    }

    for(auto it = std::begin(states); it != std::end(states); it++)
    {
        for(Transition t : (*it).second.transitions)
        {
            strs << (*it).second.identifier
                 << " -> "
                 << t.target
                 << "[label=\""
                 << t.weight.toString()
                 << "\"];";
        }
    }

    strs << "}";

    return strs.str();
}
