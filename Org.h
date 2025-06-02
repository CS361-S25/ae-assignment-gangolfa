#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/base/Ptr.hpp"

/*
    Organism is the base class that cow and grass inherit from.
    It includes bassic getter methods for points, species number, process and check reproduction.

*/
class Organism
{
protected:
    double points;
    emp::Ptr<emp::Random> random;

public:
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : points(_points), random(_random) {}

    virtual ~Organism() {}

    void SetPoints(double _in) { points = _in; }
    void AddPoints(double _in) { points += _in; }
    void SubtractPoints(double _in) { points -= _in; }
    double GetPoints() const { return points; }

    virtual int GetSpecies() const = 0;

    virtual void Process(int more_points)
    {
        points += more_points;
    }

    virtual emp::Ptr<Organism> CheckReproduction() = 0;
};

#endif