//
// Created by u on 21.11.21.
//

#include <vector>
#include <utility>
#include <iostream>
#include <random>
#include <map>
#include "../Organism/Organism.h"
#include "../Mutation.h"

#ifndef ARTIFICIALLIFE_ENVIRONMENT_H
#define ARTIFICIALLIFE_ENVIRONMENT_H

class Environment {
private:
    double food;
    double refill_rate;
    std::vector<Organism> population;
    void del_organism(size_t idx);
    void shuffle();
    std::default_random_engine rng;

public:
    Environment(double food, double refill_rate, std::vector<Organism> population);
    size_t update();
    std::map<std::string, size_t> get_population_size_by_name();
    size_t get_population_size_total();
    std::vector<Mutation> get_best_mutation_chain();
    [[nodiscard]] double get_food() const;
    std::map<std::string, size_t> get_population_size_by_mutations();
};

#endif //ARTIFICIALLIFE_ENVIRONMENT_H
