#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

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

    ~OrgWorld()
    {
    }

    emp::Ptr<Organism> ExtractOrganism(int i)
    {
        emp::Ptr<Organism> org = pop[i];
        pop[i] = nullptr;
        return org;
    }

    void Update()
    {
        emp::World<Organism>::Update();

        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
        schedule = emp::GetPermutation(random, GetSize());

        for (int i : schedule)
        {
            if (!IsOccupied(i))
                continue; // skip if org is null
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring)
            {
                DoBirth(*offspring, i);
            }

            int species = GetOrg(i).GetSpecies();
            if (species == 1) // Cow
            {
                emp::WorldPosition next_pos = GetRandomNeighborPos(i);
                if (IsOccupied(next_pos))
                {
                    emp::Ptr<Organism> next_org = pop[next_pos.GetIndex()];
                    int next_species = next_org->GetSpecies();
                    // If Next postion is species 0, then eat it
                    if (next_species == 0)
                    {
                        next_org->SetPoints(0);
                        RemoveOrgAt(next_pos);
                        // Give points to the cow
                        std::cout << "Cow ate grass" << std::endl;
                        pop[i]->AddPoints(200);
                    }
                    if (next_species == 1)
                    {
                        // If next position is species 1, then move to a random position
                        next_pos = GetRandomNeighborPos(i);
                    }
                }
                else
                {
                    pop[i]->SubtractPoints(10);
                    if (pop[i]->GetPoints() < -1000)
                    {
                        std::cout << "Cow died" << std::endl;
                        RemoveOrgAt(i);

                        continue;
                    }
                }
                AddOrgAt(ExtractOrganism(i), next_pos);
            }
            if (species == 0)
            {
                pop[i]->Process(100);
            }
        }
    }
};
#endif