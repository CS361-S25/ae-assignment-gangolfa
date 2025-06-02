#ifndef GRASS_H
#define GRASS_H

#include "Org.h"
#include "emp/base/Ptr.hpp"

/*
    Grass class inherits from Organism class
    Species number is 0
    Reproduces at 1000 points
*/
class Grass : public Organism
{
public:
    Grass(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {}

    int GetSpecies() const override { return 0; }

    void Process(int more_points) override
    {
        points += more_points; // Grows over time
    }

    // Grass has it's own reproduction function that returns a new grass organism
    emp::Ptr<Organism> CheckReproduction() override
    {
        // If it has 1000 points, it can reproduce
        if (points >= 1000)
        {
            emp::Ptr<Organism> offspring = emp::NewPtr<Grass>(random, 0);
            points -= 1000;
            return offspring;
        }
        return nullptr;
    }
};

#endif