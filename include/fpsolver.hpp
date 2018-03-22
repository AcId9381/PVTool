#ifndef FPSOLVER_HPP_INCLUDED
#define FPSOLVER_HPP_INCLUDED



#include "epdg.hpp"
#include "assignment.hpp"

namespace PVTool
{
    class FixedPointSolver
    {
    public:
        FixedPointSolver(EPDG *epdg);
        virtual ~FixedPointSolver();

        const EPDG *dependencyGraph;
        const int N_configurations;
        const int N_components;

        Assignment **lfp();

    private:
        Assignment **update(Assignment **prev, unsigned cid);
        Assignment *updateConfiguration(EPDG::Configuration *c, Assignment **prev);
        Assignment **bottom();
    };
}


#endif // FPSOLVER_HPP_INCLUDED
