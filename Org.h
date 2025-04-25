#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism
{
private:
    double points;
    emp::Ptr<emp::Random> random;
    int species;

public:
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0, int _species = 0) : points(_points), random(_random), species(_species) { ; }

    void SetPoints(double _in) { points = _in; }
    void AddPoints(double _in) { points += _in; }
    int GetPoints() { return points; }
    int GetSpecies() const { return species; }

    void Process(int more_points)
    {
        std::cout << "Processing" << std::endl; // feel free to get rid of this
        points = points + more_points;
    }
    emp::Ptr<Organism> CheckReproduction()
    {
        std::cout << "Reproducing" << std::endl;
        std::cout << points << std::endl;
        if (points >= 1000)
        {

            emp::Ptr<Organism> offspring = new Organism(random, 0, species);
            offspring->SetPoints(0);
            points = points - 1000;
            return offspring;
        }
        else
        {
            return nullptr;
        }
    }
};
#endif