#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "Cow.h"
#include "Grass.h"

#include "Org.h"

class OrgWorld : public emp::World<Organism>
{
    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;
    int points = 0;

public:
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random)
    {
        random_ptr.New(_random);
    }

    ~OrgWorld() {}

    emp::Ptr<Organism> ExtractOrganism(int i)
    {
        emp::Ptr<Organism> org = pop[i];
        pop[i] = nullptr;
        return org;
    }
    /*
        Update is the main method and is run many times throughout the simulation.
    */
    void Update()
    {
        emp::World<Organism>::Update();
        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());

        // For each organism in the schedule, handle its behavior
        for (int i : schedule)
        {
            if (!IsOccupied(i))
                continue;

            // Can this organism reproduce?
            HandleReproduction(i);

            // Check species
            int species = GetOrg(i).GetSpecies();

            // If cow, handle cow behavior
            if (species == 1)
            {
                HandleCowBehavior(i);
            }

            // If grass, handle grass behavior
            else if (species == 0)
            {
                HandleGrassBehavior(i);
            }
        }
    }

private:
    /*
    Input: int (position in the population)
    Uses int to check if a member in the population of the organisms can reproduce,
    If it can, then that organism should reproduce. Works for both grass and cow organisms.
    */
    void HandleReproduction(int i)
    {
        emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
        if (offspring)
        {
            // Place offspring in world
            AddOrgAt(offspring, GetRandomNeighborPos(i));
        }
    }
    /*
    Input: int (position in the population)
    Checks a neighbor position of the cow. If the cow has found grass, it should eat the grass and gain points.
    If it finds another cow, it should try again.

    Otherwise, no grass is found. Points should be subtracted, and check if cow should die.
    */
    void HandleCowBehavior(int i)
    {
        emp::WorldPosition next_pos = GetRandomNeighborPos(i);

        // Look for grass
        if (IsOccupied(next_pos))
        {
            emp::Ptr<Organism> next_org = pop[next_pos.GetIndex()];
            int next_species = next_org->GetSpecies();

            if (next_species == 0) // Grass
            {
                next_org->SetPoints(0);
                RemoveOrgAt(next_pos);
                std::cout << "Cow ate grass" << std::endl;
                pop[i]->AddPoints(200);
            }
            else if (next_species == 1) // Another cow
            {
                next_pos = GetRandomNeighborPos(i);
            }
        }
        // Found no grass so subtract points
        else
        {
            pop[i]->SubtractPoints(10);
            if (pop[i]->GetPoints() < -1000)
            {
                std::cout << "Cow died" << std::endl;
                RemoveOrgAt(i);
                return;
            }
        }

        // Move the cow to another square in the grid
        AddOrgAt(ExtractOrganism(i), next_pos);
    }
    /*
    Input: int (position in the population)
    This is a boring method. The grass gets 100 points for every step of update.
    */
    void HandleGrassBehavior(int i)
    {
        pop[i]->Process(100);
    }
};

#endif