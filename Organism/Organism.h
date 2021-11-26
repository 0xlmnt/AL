//
// Created by u on 21.11.21.
//

#ifndef ARTIFICIALLIFE_ORGANISM_H
#define ARTIFICIALLIFE_ORGANISM_H

#include <string>
#include <functional>
#include <random>
#include "../Configuration.h"
#include "../Mutation.h"

struct OrganismStep{
    bool is_ready_to_divide;
    double amount_food_consumed;
};

struct Uptake{
    double value;
};

class Organism{
private:
    std::string species = "unknown";
    double size{};
    double division_threshold{};
    double uptake_coeff{};
    double metabolism_coeff{};
    double size_multiplier{};
    size_t number_of_divisions{};

    std::vector<Mutation> mutations{};

    std::default_random_engine mut_rng;

    std::function<double(double, double)> f_uptake;
    std::function<double(double, double)> f_metabolism;

    bool alive{true};

    OrganismStep update(Uptake uptake);
    Mutation get_mutation();
    void mutate(Mutation mutation);


public:
    Organism(std::string species, double size, double division_threshold, double uptake_coeff, double metabolism_coeff, double size_multiplier,
             std::function<double(double, double)> uptakeRate, std::function<double(double, double)> metabolicRate);

    OrganismStep update(double available_food);
    OrganismStep update();

    void divide(std::vector<Organism>* vec);

    double get_size() const;
    std::string get_name();
    size_t get_number_of_divisions();
    void set_number_of_divisions(size_t num);
    std::vector<Mutation> get_mutations();
    bool is_alive() const;

    Mutation mutate();
};

#endif //ARTIFICIALLIFE_ORGANISM_H
