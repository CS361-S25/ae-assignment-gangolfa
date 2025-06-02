#ifndef COW_H
#define COW_H

#include "Org.h"
#include "emp/base/Ptr.hpp"

/*
    Cow inherits from Organism Class
    Species number is 1
    Reproduces at 1000 points
*/
class Cow : public Organism
{
public:
    Cow(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {}

    int GetSpecies() const override { return 1; }

    void Process(int) override
    {
        // Cows don’t gain points passively
    }

    // Cow has it's own reproduction function that returns a new cow
    emp::Ptr<Organism> CheckReproduction() override
    {
        // If it has 1000 points, it can reporoduce
        if (points >= 1000)
        {
            emp::Ptr<Organism> offspring = emp::NewPtr<Cow>(random, 0);
            points -= 1000;
            return offspring;
        }
        return nullptr;
    }
};

#endif