//
// Created by u on 21.11.21.
//

#include <vector>
#include <utility>
#include "../Organism/Organism.h"

#ifndef ARTIFICIALLIFE_ENVIRONMENT_H
#define ARTIFICIALLIFE_ENVIRONMENT_H

class Environment {
private:
    double food;
    double refill_rate;
    std::vector<Organism> population;
    void del_organism(size_t idx);

public:
    Environment(double food, double refill_rate, std::vector<Organism> population);
    size_t update();
    size_t get_population_size();
    double get_food() const;
};

#endif //ARTIFICIALLIFE_ENVIRONMENT_H
