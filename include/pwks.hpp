#ifndef PWKS_HPP_INCLUDED
#define PWKS_HPP_INCLUDED

#include <string>
#include <set>
#include <list>
#include <unordered_map>

namespace PVTool::PWKS
{
    class Model
    {
    public:
        class Expression
        {
        public:
            typedef struct term
            {
                static bool compare(const term &first, const term &second);

                unsigned coefficient;
                std::string symbol;
            } term;

            Expression();
            Expression(term t);
            Expression(std::list<term> tl);
            virtual ~Expression();

            void add(term t);
            void normalize();
            std::set<std::string> symbols() const;
            std::string toString() const;
            std::list<term> terms;
        };
        class Transition
        {
        public:
            Transition(Expression wgt, std::string tgt);
            virtual ~Transition();

            std::string toString() const;

            const Expression weight;
            const std::string target;
        };

        class State
        {
        public:
            State(std::string sid, std::list<std::string> props,
                  std::list<Transition> trans);
            virtual ~State();

            bool has_prop(std::string prop) const;
            std::string toString() const;

            const std::string identifier;
            const std::list<std::string> propositions;
            const std::list<Transition> transitions;
        };

        Model(std::list<State> slist);
        Model();
        virtual ~Model();

        bool insert(State s);
        bool insert(std::list<State> slist);
        bool contains(std::string sid) const;
        State *get(std::string sid);
        std::set<std::string> symbols() const;
        std::string toString() const;
        std::string toDot() const;

    private:
        bool insert(State s, bool verify);
        bool verify_transitions(State s) const;
        bool verify_transitions(std::list<State> slist) const;

        std::unordered_map<std::string, State> states;
    };
}

#endif // PWKS_HPP_INCLUDED
