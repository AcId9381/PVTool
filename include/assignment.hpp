#ifndef ASSIGNMENT_HPP_INCLUDED
#define ASSIGNMENT_HPP_INCLUDED

#include <list>
#include <unordered_map>
#include <string>

#include "epdg.hpp"

namespace PVTool
{
    class Expression;

    class Assignment
    {
    public:
        virtual ~Assignment() = 0;
        virtual std::string toString() const;
    };

    class Infinity : public Assignment
    {
    public:
        virtual ~Infinity();
        std::string toString() const override;
    };

    class Cover : public Assignment
    {
    public:
        Cover(Assignment *succ, double cond);
        virtual ~Cover();
        std::string toString() const override;

        const Assignment *successor_assignment;
        const double cover_condition;
    };

    class Negation : public Assignment
    {
    public:
        Negation(Assignment *succ);
        virtual ~Negation();
        std::string toString() const override;

        const Assignment *successor_assignment;
    };

    class Expression : public Assignment, public EPDG::Expression
    {
    public:
        Expression(const std::unordered_map<unsigned,std::string> *symb);
        Expression(const EPDG::Expression &exp);
        virtual ~Expression();
        std::string toString() const override;
    };

    class Plus : public Assignment
    {
    public:
        Plus(const Expression wgt, const Assignment *ass);
        virtual ~Plus();
        std::string toString() const override;

        const Expression weight;
        const Assignment *assignment;
    };

    class Max : public Assignment
    {
    public:
        Max(std::list<Assignment*> ops);
        virtual ~Max();
        std::string toString() const override;

        std::list<Assignment*> operands;
    };

    class Min : public Assignment
    {
    public:
        Min(std::list<Assignment*> ops);
        virtual ~Min();
        std::string toString() const override;

        std::list<Assignment*> operands;
    };
}

#endif // ASSIGNMENT_HPP_INCLUDED
