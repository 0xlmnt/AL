//
// Created by u on 26.11.21.
//

#ifndef ARTIFICIALLIFE_MUTATION_H
#define ARTIFICIALLIFE_MUTATION_H

#include <string>
#include <functional>
#include <random>
#include "Configuration.h"

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

std::string mutation_chain_to_string(const std::vector<Mutation>& vec);



#endif //ARTIFICIALLIFE_MUTATION_H
