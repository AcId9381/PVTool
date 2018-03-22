#include <iostream>
#include <fstream>
#include "wctl.driver.hpp"
#include "pwks.driver.hpp"
#include "epdg.hpp"
#include "fpsolver.hpp"
#include "assignment.hpp"
#include "pwks.hpp"
#include "epdg.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    PVTool::WCTL::Driver logic_driver;
    PVTool::PWKS::Driver model_driver;
    std::string init_state;
    PVTool::PWKS::Model *model;
    PVTool::WCTL::StateFormula *formula;

    if(argc < 4)
    {
        string formula_string = "NoT E(EX[1]false)U[2]True";
        string model_string = "s1{a} <2p+q+p>s2 s2{b}";
        init_state = "s1";
        logic_driver.parse(formula_string);
        model_driver.parse(model_string);
    }
    else
    {
        /*ifstream model_in;
        model_in.open(argv[1]);
        model_driver.parse(&model_in);
        model_in.close();

        ifstream formula_in;
        formula_in.open(argv[2]);
        logic_driver.parse(&formula_in);
        formula_in.close(); */

	model_driver.parse(argv[1]);
	logic_driver.parse(argv[2]);
        init_state = argv[3];
    }

    model = model_driver.model();
    formula = logic_driver.formula();

    PVTool::EPDG g(init_state, formula, model);

    ofstream epdg_out;
    epdg_out.open("epdg.dot");
    epdg_out << g.toDot();
    epdg_out.close();

    PVTool::FixedPointSolver fp_solver(&g);

    PVTool::Assignment **lfp = fp_solver.lfp();

    std::cout << lfp[0]->toString() << std::endl;

}
