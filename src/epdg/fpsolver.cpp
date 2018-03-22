#include "fpsolver.hpp"
#include <iostream>
#include <typeinfo>

using namespace PVTool;

FixedPointSolver::FixedPointSolver(EPDG *epdg)
    : dependencyGraph(epdg),
      N_configurations(epdg->next_id),
      N_components(epdg->components.size())
{
    //ctor
}

FixedPointSolver::~FixedPointSolver()
{
    //dtor
}

Assignment **FixedPointSolver::lfp()
{
    Assignment **res = bottom();

    for(int i = 0; i < N_components; i++)
    {
        for(unsigned j = 0; j < dependencyGraph->components.find((unsigned)i)->second.size(); j++)
        {
            res = update(res, i);
        }
    }
    return res;
}

Assignment **FixedPointSolver::update(Assignment **prev, unsigned cid)
{
    Assignment **res = (Assignment**) malloc(N_configurations * sizeof(Assignment*));

    for(int i = 0U; i < N_configurations; i++)
    {
        res[i] = prev[i];
    }

    for(EPDG::Configuration *c : dependencyGraph->components.find((unsigned)cid)->second)
    {
        res[c->identifier] = updateConfiguration(c, prev);
    }

    free(prev);

    return res;
}


Assignment *FixedPointSolver::updateConfiguration(EPDG::Configuration *c, Assignment **prev)
{
    if(c->hedges != nullptr)
    {
        if(c->hedges->empty())
        {
            std::cout << "This should not happen!" << std::endl;
            return new Expression(&(dependencyGraph->symbols));
        }
        else
        {
            std::list<Assignment*> min_ops;
            for(EPDG::HyperEdge *e : *(c->hedges))
            {
                std::list<Assignment*> max_ops;
                for(EPDG::HyperEdge::target t : e->target_set)
                {
                    if( typeid(*prev[t.first->identifier]) == typeid(Infinity) )
                    {
                        for(Assignment *a : max_ops)
                        {
                            delete(a);
                        }
                        max_ops.clear();
                        max_ops.push_back(new Infinity);
                        break;
                    }
                    else
                    {
                        max_ops.push_back(new Plus(t.second, prev[t.first->identifier]));
                    }
                }

                if(max_ops.size() == 0)
                {
                    min_ops.push_back(new Expression(&(dependencyGraph->symbols)));
                }
                else if(max_ops.size() == 1)
                {
                    min_ops.push_back(max_ops.front());
                }
                else
                {
                    min_ops.push_back(new Max(max_ops));
                }
            }
            if(min_ops.size() == 0)
            {
                return new Infinity;
            }
            else if(min_ops.size() == 1)
            {
                return min_ops.front();
            }
            else
            {
                return new Min(min_ops);
            }
        }
    }
    else if(c->nedge != nullptr)
    {
        return new Negation(prev[c->nedge->target->identifier]);
    }
    else if(c->cedge != nullptr)
    {
        return new Cover(prev[c->cedge->target->identifier], c->cedge->condition);
    }
    else
    {
        return new Infinity();
    }
}

Assignment **FixedPointSolver::bottom()
{
    Assignment **res = (Assignment**) malloc(N_configurations * sizeof(Assignment*));

    for(int i = 0U; i < N_configurations; i++)
    {
        res[i] = new Infinity();
    }

    return res;
}
