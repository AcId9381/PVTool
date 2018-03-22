#include <list>
#include <string>
#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <sstream>
#include <set>
#include <stdlib.h>
#include <algorithm>

#include "epdg.hpp"
#include "pwks.hpp"
#include "wctl.hpp"

using namespace PVTool;

/****** Expression ******/

EPDG::Expression::Expression(const std::unordered_map<unsigned,std::string> *symb)
    : symbols(symb)
{
    coefficients = (int*)calloc(symb->size(), sizeof(int));
}

EPDG::Expression::Expression(const PWKS::Model::Expression &exp, const std::unordered_map<unsigned,std::string> *symb)
    : Expression(symb)
{
    for(PWKS::Model::Expression::term t : exp.terms)
    {
        const std::string symbol = t.symbol;
        auto it = std::find_if(std::begin(*symb), std::end(*symb),
                               [symbol](const auto &m) -> bool { return m.second == symbol; });
        unsigned key = it->first;
        coefficients[key] = t.coefficient;
    }
}

EPDG::Expression::Expression(const EPDG::Expression &obj)
    : coefficients(obj.coefficients),
      symbols(obj.symbols)
{
    //ctor
}

EPDG::Expression::~Expression()
{
    //free(coefficients);
}

std::string EPDG::Expression::toString()
{
    std::ostringstream strs;
    bool first = true;

    for(unsigned i = 0; i < symbols->size(); i++)
    {
        if(coefficients[i])
        {
            if(!first)
                strs << " + ";
            strs << coefficients[i] << symbols->find(i)->second;
            first = false;
        }
        else if(symbols->find(i)->second == "" && first)
        {
            strs << coefficients[i];
            first = false;
        }
    }

    return strs.str();
}

/****** EDGE ******/

EPDG::Edge::Edge(EPDG::Configuration *src)
    : source(src)
{
    //ctor
}

EPDG::Edge::~Edge()
{
    //dtor
}



/****** HyperEdge ******/

EPDG::HyperEdge::HyperEdge(EPDG::Configuration *src)
    : EPDG::Edge(src)
{
    //ctor
}

EPDG::HyperEdge::HyperEdge(Configuration *src, std::list<EPDG::HyperEdge::target> tgts)
    : HyperEdge(src)
{
    target_set = tgts;
}

EPDG::HyperEdge::~HyperEdge()
{
    //dtor
}

std::string EPDG::HyperEdge::toString()
{
    return "";
}



/****** NegationEdge ******/

EPDG::NegationEdge::NegationEdge(EPDG::Configuration *src, EPDG::Configuration *tgt)
    : EPDG::Edge(src),
      target(tgt)
{
    //ctor
}

EPDG::NegationEdge::~NegationEdge()
{
    //dtor
}



/****** CoverEdge ******/

EPDG::CoverEdge::CoverEdge(EPDG::Configuration *src, EPDG::Configuration *tgt, double cond)
    : NegationEdge(src, tgt),
      condition(cond)
{
    //ctor
}

EPDG::CoverEdge::~CoverEdge()
{
    //dtor
}



/****** Configuration ******/

EPDG::Configuration::Configuration(const unsigned nid, const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::StateFormula *form)
    : state(s),
      identifier(nid),
      formula(form)
{
    component = cid;
    hedges = nullptr;
    nedge = nullptr;
    cedge = nullptr;
}

EPDG::Configuration::~Configuration()
{
    //delete(formula);
    delete(hedges);
    delete(nedge);
    delete(cedge);
}

bool EPDG::Configuration::insert(PVTool::EPDG::Edge *e)
{
    if(cedge != nullptr)
    {
        std::cerr << "Error inserting edge: node already has a cover-edge"
                  << std::endl;
        return false;
    }
    else if(nedge != nullptr)
    {
        std::cerr << "Error inserting edge: node already has a negation-edge"
                  << std::endl;
        return false;
    }
    else if(hedges != nullptr && typeid(*e) != typeid(HyperEdge))
    {
        std::cerr << "Error inserting edge: node already has hyper-edges"
                  << std::endl;
    }
    else if(e->source->identifier != identifier)
    {
        std::cerr << "Error inserting edge: edge have wrong source id"
                  << std::endl;
        return false;
    }


    if(typeid(*e) == typeid(CoverEdge))
    {
        cedge = (CoverEdge*)e;
    }
    else if(typeid(*e) == typeid(NegationEdge))
    {
        nedge = (NegationEdge*)e;
    }
    else if(typeid(*e) == typeid(HyperEdge))
    {
        if(hedges == nullptr)
            hedges = new std::list<HyperEdge*>;

        hedges->push_back((HyperEdge*)e);
    }
    else
    {
        std::cerr << "Error inserting edge: unknown edge type"
                  << typeid(e).name() << std::endl;
        return false;
    }

    return true;
}

void EPDG::Configuration::update_component(unsigned cid, unsigned *N_components) const
{
    if(component < cid)
        component = cid;

    // Update number of components
    if(*N_components < cid)
        *N_components = cid;

    if(cedge != nullptr)
    {
        if(cedge->target->component <= component)
            cedge->target->update_component(cid + 1, N_components);
    }
    else if(nedge != nullptr)
    {
        if(nedge->target->component <= component)
            nedge->target->update_component(cid + 1, N_components);
    }
    else if(hedges != nullptr)
    {
        for(auto it : *hedges)
        {
            for(auto iit : it->target_set)
            {
                if(iit.first->component < component)
                    iit.first->update_component(cid, N_components);
            }
        }
    }
}



/****** EPDG ******/

EPDG::EPDG(std::string init_state, PVTool::WCTL::StateFormula *form, PVTool::PWKS::Model *m)
    : model(m),
      formula(form)
{
    next_id = 0;
    N_components = 0;

    if(!model->contains(init_state))
    {
        std::cerr << "Error: initial state \"" << init_state << "\" not found in model." << std::endl;
        return;
    }
    else
    {
        makeSymbolTable();
        make_configuration(0U, model->get(init_state), form);
        make_components();
    }
}

EPDG::~EPDG()
{
    delete(model);
    delete(formula);

    for(auto it : components)
    {
        for(auto itt : it.second)
        {
            delete(itt);
        }
    }
}

std::string EPDG::toString()
{
    return "";
}

std::string EPDG::toDot()
{
    std::ostringstream strs;
    unsigned cluster = 0U;

    // Create graph
    strs << "digraph G {" << std::endl;

    // Set top-down direction
    strs << "rankdir=TB;" << std::endl;

    // Make clusters
    for(unsigned cid = N_components; ; cid--)
    {
        // Create new cluster
        strs << "subgraph cluster_" << cluster++ << " {" << std::endl;

        // Set label from component id
        strs << "label=\"C" << cid << "\";" << std::endl;

        // Left justify label
        strs << "labeljust=\"l\";" << std::endl;

        // Set style to rounded corners
        strs << "style=rounded;" << std::endl;

        // Set color to black
        strs << "color=black;" << std::endl;

        // Create nodes
        auto it = components.find(cid);
        std::list<Configuration *> comp = it->second;
        for(Configuration *conf : comp)
        {
            strs << conf->identifier
                 << "[shape=box, label=\"<"
                 << conf->state->identifier
                 << ", "
                 << conf->formula->toString()
                 << ">\"];"
                 << std::endl;

             // Create additional nodes for hyper edges
            if(conf->hedges != nullptr)
            {
                unsigned i = 0U;
                for(HyperEdge *e : *(conf->hedges))
                {
                    if(std::empty(e->target_set))
                    {
                        strs << "E"
                             << conf->identifier
                             << "[label=\"&empty;\", color=white];"
                             << std::endl;
                    }
                    else if(std::size(e->target_set) > 1)
                    {
                        std::string hnode = std::string("H")
                                + std::to_string(conf->identifier)
                                + std::string("_")
                                + std::to_string(i);
                        strs << hnode
                        << " [style=invisible, fixedsize=true, height=0, width=0];"
                        << std::endl;
                        i++;
                    }
                }
            }
        }

        // Close cluster
        strs << "}" << std::endl;

        if(cid == 0U)
            break;
    }

    for(unsigned cid = N_components; ; cid--)
    {
        auto it = components.find(cid);
        std::list<Configuration *> comp = it->second;
        for(Configuration *conf : comp)
        {
            if(conf->nedge != nullptr)
            {
                strs << conf->identifier
                     << " -> "
                     << conf->nedge->target->identifier
                     << "[color=\"black:invis:black\"];"
                     << std::endl;
            }
            else if(conf->cedge != nullptr)
            {
                strs << conf->identifier
                     << " -> "
                     << conf->cedge->target->identifier
                     << "[style=dashed, label=\""
                     << conf->cedge->condition
                     << "\"];"
                     << std::endl;
            }
            else if(conf->hedges != nullptr)
            {
                unsigned i = 0U;
                for(HyperEdge *e : *(conf->hedges))
                {
                    if(std::empty(e->target_set))
                    {
                        strs << conf->identifier
                             << " -> E"
                             << conf->identifier
                             << ";"
                             << std::endl;
                    }
                    else if(std::size(e->target_set) == 1)
                    {
                        HyperEdge::target tgt = e->target_set.front();
                        strs << conf->identifier
                             << " -> "
                             << tgt.first->identifier
                             << "[label=\""
                             << tgt.second.toString()
                             << "\"];"
                             << std::endl;
                    }
                    else
                    {
                        std::string hnode = std::string("H")
                                + std::to_string(conf->identifier)
                                + std::string("_")
                                + std::to_string(i);

                        strs << conf->identifier
                             << " -> "
                             << hnode
                             << "[dir=none];"
                             << std::endl;

                        for(HyperEdge::target tgt : e->target_set)
                        {
                            strs << hnode
                                 << " -> "
                                 << tgt.first->identifier
                                 << "[label=\""
                                 << tgt.second.toString()
                                 << "\"];"
                                 << std::endl;
                        }
                        i++;
                    }
                }
            }
        }

        if(cid== 0U)
            break;
    }
    // Close graph
    strs << "}"
         << std::endl;

    return strs.str();
}

bool EPDG::insert(Configuration *conf)
{
    std::string key = conf->state->identifier + conf->formula->toString();
    return configurations.insert({key, conf}).second;
}

void EPDG::makeSymbolTable()
{
    std::set<std::string> sym = model->symbols();
    unsigned i = 0U;

    for(auto it : sym)
    {
        symbols.insert({i++, it});
    }
}

EPDG::Configuration *EPDG::get(std::string sid, std::string fstring)
{
    auto it = configurations.find(sid + fstring);

    if(it != std::end(configurations))
        return it->second;
    else
        return nullptr;
}

EPDG::Configuration *EPDG::make_configuration(const unsigned cid, const PWKS::Model::State *s, const WCTL::StateFormula *form)
{
    // Update number of components
    if(N_components < cid)
        N_components = cid;

    Configuration *tmp = get(s->identifier, form->toString());

    if(tmp != nullptr)
    {
        tmp->update_component(cid, &N_components);
        return tmp;
    }
    else if(typeid(*form) == typeid(WCTL::True))
    {
        return make_true(cid, s, (WCTL::True*)form);
    }
    else if(typeid(*form) == typeid(WCTL::False))
    {
        return make_false(cid, s, (WCTL::False*)form);
    }
    else if(typeid(*form) == typeid(WCTL::Proposition))
    {
        return make_proposition(cid, s, (WCTL::Proposition*)form);
    }
    else if(typeid(*form) == typeid(WCTL::Negation))
    {
        return make_negation(cid, s, (WCTL::Negation*)form);
    }
    else if(typeid(*form) == typeid(WCTL::Conjunction))
    {
        return make_conjunction(cid, s, (WCTL::Conjunction*)form);
    }
    else if(typeid(*form) == typeid(WCTL::Disjunction))
    {
        return make_disjunction(cid, s, (WCTL::Disjunction*)form);
    }
    else if(typeid(*form) == typeid(WCTL::Exists))
    {
        return make_exists(cid, s, (WCTL::Exists*)form);
    }
    else if(typeid(*form) == typeid(WCTL::Forall))
    {
        return make_forall(cid, s, (WCTL::Forall*)form);
    }
    else
    {
        std::cerr << "Invalid formula class: " << typeid(form).name()
            << std::endl;
        return nullptr;
    }
}

EPDG::Configuration *EPDG::make_true(const unsigned cid, const PWKS::Model::State *s, const WCTL::True *form)
{
    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into state map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    // Insert hyper-edge with empty target set
    res->insert(new HyperEdge(res));

    return res;
}

EPDG::Configuration *EPDG::make_false(const unsigned cid, const PWKS::Model::State *s, const WCTL::False *form)
{
    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into state map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    return res;
}

EPDG::Configuration *EPDG::make_proposition(const unsigned cid, const PWKS::Model::State *s, const WCTL::Proposition *form)
{
    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into state map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    if(s->has_prop(form->proposition))
    {
        res->insert(new HyperEdge(res));
    }

    return res;
}

EPDG::Configuration *EPDG::make_negation(const unsigned cid, const PWKS::Model::State *s, const WCTL::Negation *form)
{
    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into state map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new node into node map"
                  << std::endl;
    }

    // Create successor node
    Configuration *succ = make_configuration(cid + 1U, s, form->formula);

    // Insert negation edge
    res->insert(new NegationEdge(res, succ));

    return res;
}

EPDG::Configuration *EPDG::make_conjunction(const unsigned cid, const PWKS::Model::State *s, const WCTL::Conjunction *form)
{
    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into state map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new node into node map"
                  << std::endl;
    }

    // Make successors
    Configuration *succ1 = make_configuration(cid, s, form->left);
    Configuration *succ2 = make_configuration(cid, s, form->right);

    EPDG::Expression weight(&symbols);

    // Make targets
    HyperEdge::target tgt1 = {succ1, weight};
    HyperEdge::target tgt2 = {succ2, weight};

    // Make target set
    std::list<HyperEdge::target> tset;
    tset.push_front(tgt1);
    tset.push_front(tgt2);

    // Add hyper edge
    res->insert(new HyperEdge(res, tset));

    return res;
}

EPDG::Configuration *EPDG::make_disjunction(const unsigned cid, const PWKS::Model::State *s, const WCTL::Disjunction *form)
{
    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into state map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new node into node map"
                  << std::endl;
    }

    // Make successors
    Configuration *succ1 = make_configuration(cid, s, form->left);
    Configuration *succ2 = make_configuration(cid, s, form->right);

    EPDG::Expression weight(&symbols);

    // Make targets
    HyperEdge::target tgt1 = {succ1, weight};
    HyperEdge::target tgt2 = {succ2, weight};

    // Make target sets
    std::list<HyperEdge::target> tset1;
    std::list<HyperEdge::target> tset2;
    tset1.push_front(tgt1);
    tset2.push_front(tgt2);

    // Add hyper edges
    res->insert(new HyperEdge(res, tset1));
    res->insert(new HyperEdge(res, tset2));

    return res;
}

EPDG::Configuration *EPDG::make_exists(const unsigned cid, const PWKS::Model::State *s, const WCTL::Exists *form)
{
    if(typeid(*(form->formula)) == typeid(WCTL::Next))
    {
        return make_enext(cid, s, form);
    }
    else if(typeid(*(form->formula)) == typeid(WCTL::Until))
    {
        return make_euntil(cid, s, form);
    }
    else
    {
        std::cerr << "Error: PathFormula is neither next nor until"
                  << std::endl;
        return nullptr;
    }
}

EPDG::Configuration *EPDG::make_forall(const unsigned cid, const PWKS::Model::State *s, const WCTL::Forall *form)
{
    if(typeid(*(form->formula)) == typeid(WCTL::Next))
    {
        return make_unext(cid, s, form);
    }
    else if(typeid(*(form->formula)) == typeid(WCTL::Until))
    {
        return make_uuntil(cid, s, form);
    }
    else
    {
        std::cerr << "Error: PathFormula is neither next nor until"
                  << std::endl;
        return nullptr;
    }
}

EPDG::Configuration *EPDG::make_enext(const unsigned cid, const PWKS::Model::State *s, const WCTL::Exists *form)
{
    if(typeid(*(form->formula)) != typeid(WCTL::Next))
    {
        std::cerr << "Error: Formula not a 'Next'" << std::endl;
        return nullptr;
    }

    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into configurations map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    WCTL::Next *next = (WCTL::Next*)form->formula;

    // If bound >= 0, make cover-edge; otherwise make hyper-edges
    if(form->formula->bound >= 0)
    {
        // Make successor next formula
        WCTL::Next *snext = new WCTL::Next(-1, next->formula);

        // Make successor exists formula
        WCTL::Exists *sexists = new WCTL::Exists(snext);

        // Make successor configuration
        Configuration *succ = make_configuration(cid + 1U, s, sexists);

        // Insert cover-edge
        res->insert(new CoverEdge(res, succ, next->bound));
    }
    else if(!std::empty(s->transitions))
    {
        Configuration *succ;
        for(PWKS::Model::Transition t : s->transitions)
        {
            // Make successor configuration
            succ = make_configuration(cid, model->get(t.target), next->formula);

            EPDG::Expression weight(t.weight, &symbols);

            // Make target
            HyperEdge::target tgt = {succ, weight};

            // Make target list
            std::list<HyperEdge::target> tlist;
            tlist.push_back(tgt);

            // Insert hyper-edge
            res->insert(new HyperEdge(res, tlist));
        }
    }

    return res;
}

EPDG::Configuration *EPDG::make_unext(const unsigned cid, const PWKS::Model::State *s, const WCTL::Forall *form)
{
    if(typeid(*(form->formula)) != typeid(WCTL::Next))
    {
        std::cerr << "Error: Formula not a 'Next'" << std::endl;
        return nullptr;
    }

    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into configurations map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    WCTL::Next *next = (WCTL::Next*)form->formula;

    // If bound >= 0, make cover-edge; otherwise make hyper-edges
    if(form->formula->bound >= 0)
    {
        // Make successor next formula
        WCTL::Next *snext = new WCTL::Next(-1, next->formula);

        // Make successor forall formula
        WCTL::Forall *sforall = new WCTL::Forall(snext);

        // Make successor configuration
        Configuration *succ = make_configuration(cid + 1U, s, sforall);

        // Insert cover-edge
        res->insert(new CoverEdge(res, succ, next->bound));
    }
    else if(!std::empty(s->transitions))
    {
        Configuration *succ;
        std::list<HyperEdge::target> tlist;
        for(PWKS::Model::Transition t : s->transitions)
        {
            // Make successor configuration
            succ = make_configuration(cid, model->get(t.target), next->formula);

            EPDG::Expression weight(t.weight, &symbols);

            // Make target
            HyperEdge::target tgt = {succ, weight};

            // Push new target to target list
            tlist.push_back(tgt);
        }
        // Insert hyper-edge
        res->insert(new HyperEdge(res, tlist));
    }

    return res;
}

EPDG::Configuration *EPDG::make_euntil(const unsigned cid, const PWKS::Model::State *s, const WCTL::Exists *form)
{
    if(typeid(*(form->formula)) != typeid(WCTL::Until))
    {
        std::cerr << "Error: Formula not an 'Until'" << std::endl;
        return nullptr;
    }

    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into configurations map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    Configuration *succ;
    WCTL::Until *until = (WCTL::Until*)form->formula;

    // If bound >= 0, make cover-edge; otherwise make hyper-edges
    if(until->bound >= 0)
    {
        // Make successor until formula
        WCTL::Until *suntil = new WCTL::Until(-1, until->left, until->right);

        // Make successor exists formula
        WCTL::Exists *sexists = new WCTL::Exists(suntil);

        // Make successor configuration
        succ = make_configuration(cid + 1U, s, sexists);

        // Insert cover-edge
        res->insert(new CoverEdge(res, succ, until->bound));
    }
    else
    {
        EPDG::Expression zero_exp(&symbols);

        // Make successors for rhs formula
        Configuration *right = make_configuration(cid, s, until->right);

        // Make target for rhs formula
        HyperEdge::target right_tgt = {right, zero_exp};

        // Make target list for right target
        std::list<HyperEdge::target> right_tlist;
        right_tlist.push_back(right_tgt);

        // Add hyper-edge to right target
        res->insert(new HyperEdge(res, right_tlist));

        if(!std::empty(s->transitions))
        {
            Configuration *left = make_configuration(cid, s, until->left);
            HyperEdge::target left_tgt = {left, zero_exp};

            for(PWKS::Model::Transition t : s->transitions)
            {
                // Make successor configuration
                succ = make_configuration(cid, model->get(t.target), form);

                EPDG::Expression weight(t.weight, &symbols);

                // Make target
                HyperEdge::target tgt = {succ, weight};

                // Make target list
                std::list<HyperEdge::target> tlist;
                tlist.push_back(tgt);
                tlist.push_back(left_tgt);

                // Insert hyper-edge
                res->insert(new HyperEdge(res, tlist));
            }
        }
    }
    return res;
}

EPDG::Configuration *EPDG::make_uuntil(const unsigned cid, const PWKS::Model::State *s, const WCTL::Forall *form)
{
    if(typeid(*(form->formula)) != typeid(WCTL::Until))
    {
        std::cerr << "Error: Formula not an 'Until'" << std::endl;
        return nullptr;
    }

    Configuration *res = new Configuration(next_id++, cid, s, form);

    // Insert into configurations map
    if(!insert(res))
    {
        std::cerr << "Error: could not insert new configuration into configurations map"
                  << std::endl;
    }

    Configuration *succ;
    WCTL::Until *until = (WCTL::Until*)form->formula;

    // If bound >= 0, make cover-edge; otherwise make hyper-edges
    if(until->bound >= 0)
    {
        // Make successor until formula
        WCTL::Until *suntil = new WCTL::Until(-1, until->left, until->right);

        // Make successor forall formula
        WCTL::Forall *sforall = new WCTL::Forall(suntil);

        // Make successor configuration
        succ = make_configuration(cid + 1U, s, sforall);

        // Insert cover-edge
        res->insert(new CoverEdge(res, succ, until->bound));
    }
    else
    {
        EPDG::Expression zero_exp(&symbols);

        // Make successors for rhs formula
        Configuration *right = make_configuration(cid, s, until->right);

        // Make target for rhs formula
        HyperEdge::target right_tgt = {right, zero_exp};

        // Make target list for right target
        std::list<HyperEdge::target> right_tlist;
        right_tlist.push_back(right_tgt);

        // Add hyper-edge to right target
        res->insert(new HyperEdge(res, right_tlist));

        if(!std::empty(s->transitions))
        {
            Configuration *left = make_configuration(cid, s, until->left);
            HyperEdge::target left_tgt = {left, zero_exp};
            // Construct target list for left formula
            std::list<HyperEdge::target> tlist;
            tlist.push_back(left_tgt);

            for(PWKS::Model::Transition t : s->transitions)
            {
                // Make successor configuration
                succ = make_configuration(cid, model->get(t.target), form);

                EPDG::Expression weight(t.weight, &symbols);

                // Make target
                HyperEdge::target tgt = {succ, weight};

                // Add target to target list
                tlist.push_back(tgt);
            }
            // Insert hyper-edge
            res->insert(new HyperEdge(res, tlist));
        }
    }
    return res;
}

void EPDG::make_components()
{
    for(auto it : configurations)
    {
        Configuration *conf = it.second;

        // Set component id
        conf->component = (N_components - conf->component);

        // Check if component already exists in the map;
        // If it exist insert configuration to configurations list for that component,
        // otherwise make new component.
        if(components.count(conf->component))
        {
            auto it = components.find(conf->component);
            std::list<Configuration*> *comp = &(it->second);
            comp->push_back(conf);
        }
        else
        {
            std::list<Configuration*> comp;
            comp.push_back(conf);
            components.insert({conf->component, comp});
        }
    }
}
