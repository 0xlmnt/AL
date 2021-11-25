//
// Created by u on 21.11.21.
//

#ifndef ARTIFICIALLIFE_ORGANISM_H
#define ARTIFICIALLIFE_ORGANISM_H

#include <string>
#include <functional>
#include <random>
#include "../Configuration.h"

struct OrganismStep{
    bool is_ready_to_divide;
    double amount_food_consumed;
};

struct Uptake{
    double value;
};

enum class MutationType{
    NONE = 0,
    DIV_THRESHOLD = 1,
    C_UPTAKE = 2,
    C_METABOLISM = 3,
    SIZE_MULTIPLIER = 4
};

struct Mutation{
    MutationType type;
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
    bool is_alive() const;

    Mutation mutate();
};

#endif //ARTIFICIALLIFE_ORGANISM_H
