#ifndef WCTL_HPP_INCLUDED
#define WCTL_HPP_INCLUDED

#include <string>

namespace PVTool::WCTL
{
    class Formula
    {
    public:
        virtual ~Formula() = 0;
        virtual std::string toString() const;
        virtual std::string toWKString() const;
    };


    class StateFormula : public Formula
    {
    public:
        virtual ~StateFormula() = 0;
    };

    class PathFormula : public Formula
    {
    public:
        PathFormula();
        PathFormula(const double bnd);
        virtual ~PathFormula() = 0;

        const double bound;
    };

    class True : public StateFormula
    {
    public:
        True();
        virtual ~True();
        std::string toString() const override;
        std::string toWKString() const override;
    };

    class False : public StateFormula
    {
    public:
        False();
        virtual ~False();
        std::string toString() const override;
        std::string toWKString() const override;
    };

    class Proposition : public StateFormula
    {
    public:
        Proposition(const std::string prop);
        virtual ~Proposition();
        std::string toString() const override;
        std::string toWKString() const override;

        const std::string proposition;
    };

    class Negation : public StateFormula
    {
    public:
        Negation(const StateFormula *form);
        Negation(const Negation &obj);
        ~Negation();
        std::string toString() const override;
        std::string toWKString() const override;

        const StateFormula *formula;
    };

    class Conjunction : public StateFormula
    {
    public:
        Conjunction(const StateFormula *l, const StateFormula *r);
        Conjunction(const Conjunction &obj);
        ~Conjunction();
        std::string toString() const override;
        std::string toWKString() const override;

        const StateFormula *left;
        const StateFormula *right;
    };

    class Disjunction : public StateFormula
    {
    public:
        Disjunction(const StateFormula *l, const StateFormula *r);
        Disjunction(const Disjunction &obj);
        ~Disjunction();
        std::string toString() const override;
        std::string toWKString() const override;

        const StateFormula *left;
        const StateFormula *right;
    };

    class Exists : public StateFormula
    {
    public:
        Exists(const PathFormula *form);
        Exists(const Exists &obj);
        ~Exists();
        std::string toString() const override;
        std::string toWKString() const override;

        const PathFormula *formula;
    };

    class Forall : public StateFormula
    {
    public:
        Forall(const PathFormula *form);
        Forall(const Forall &obj);
        ~Forall();
        std::string toString() const override;
        std::string toWKString() const override;

        const PathFormula *formula;
    };

    class Next : public PathFormula
    {
    public:
        Next(const double bnd, const StateFormula *form);
        Next(const Next &obj);
        ~Next();
        std::string toString() const override;
        std::string toWKString() const override;

        const StateFormula *formula;
    };

    class Until : public PathFormula
    {
    public:
        Until(const double bnd, const StateFormula *l, const StateFormula *r);
        Until(const Until &obj);
        ~Until();
        std::string toString() const override;
        std::string toWKString() const override;

        const StateFormula *left;
        const StateFormula *right;
    };
}

#endif // WCTL_HPP_INCLUDED
