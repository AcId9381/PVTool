#ifndef EPDG_HPP_INCLUDED
#define EPDG_HPP_INCLUDED

#include <string>
#include <list>

#include "pwks.hpp"
#include "wctl.hpp"

namespace PVTool
{
    class FixedPointSolver;
    class EPDG
    {
    public:
        friend class PVTool::FixedPointSolver;
        class Configuration;
        class Assignment;

        class Expression
        {
        public:
            Expression(const std::unordered_map<unsigned,std::string> *symb);
            Expression(const PVTool::PWKS::Model::Expression &exp, const std::unordered_map<unsigned,std::string> *symb);
            Expression(const Expression &obj);
            ~Expression();
            std::string toString();

            int *coefficients;
            const std::unordered_map<unsigned,std::string> *symbols;
        };

        class Edge
        {
        public:
            Edge(Configuration *src);
            virtual ~Edge() = 0;
            const Configuration *source;
        };

        class HyperEdge : public Edge
        {
        public:
            typedef std::pair<Configuration*, EPDG::Expression> target;

            HyperEdge(Configuration *src);
            HyperEdge(Configuration *src, std::list<target> tgts);
            ~HyperEdge();
            std::string toString();

            std::list<target> target_set;
        };

        class NegationEdge : public Edge
        {
        public:
            NegationEdge(Configuration *src, Configuration *tgt);
            ~NegationEdge();

            const Configuration *target;
        };

        class CoverEdge : public NegationEdge
        {
        public:
            CoverEdge(Configuration *src, Configuration *tgt, double cond);
            ~CoverEdge();

            const double condition;
        };

        class Configuration
        {
        public:
            class Assignment;
            friend class EPDG;
            friend class PVTool::FixedPointSolver;
            Configuration(const unsigned nid, const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::StateFormula *form);
            ~Configuration();
            bool insert(Edge *e);
            void update_component(unsigned vid, unsigned *N_components) const;

            const PVTool::PWKS::Model::State *state;
            const PVTool::WCTL::StateFormula *formula;
            const unsigned identifier;
            mutable unsigned component;

        private:
            std::list<HyperEdge*> *hedges;
            NegationEdge *nedge;
            CoverEdge *cedge;
        };

        EPDG(std::string init_state, PVTool::WCTL::StateFormula *form, PVTool::PWKS::Model *m);
        ~EPDG();
        std::string toString();
        std::string toDot();

        private:
            bool insert(Configuration *conf);
            void makeSymbolTable();
            Configuration *get(std::string sid, std::string fstring);
            Configuration *make_configuration(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::StateFormula *form);
            Configuration *make_true(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::True *form);
            Configuration *make_false(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::False *form);
            Configuration *make_proposition(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Proposition *form);
            Configuration *make_negation(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Negation *form);
            Configuration *make_conjunction(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Conjunction *form);
            Configuration *make_disjunction(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Disjunction *form);
            Configuration *make_exists(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Exists *form);
            Configuration *make_forall(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Forall *form);
            Configuration *make_enext(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Exists *form);
            Configuration *make_unext(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Forall *form);
            Configuration *make_euntil(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Exists *form);
            Configuration *make_uuntil(const unsigned cid, const PVTool::PWKS::Model::State *s, const PVTool::WCTL::Forall *form);
            void make_components();

            unsigned next_id;
            unsigned N_components;
            PVTool::PWKS::Model *model;
            PVTool::WCTL::StateFormula *formula;
            std::unordered_map<std::string, Configuration*> configurations;
            std::unordered_map<unsigned, std::list<Configuration*>> components;
            std::unordered_map<unsigned, std::string> symbols;

    };
}

#endif // EPDG_HPP_INCLUDED
