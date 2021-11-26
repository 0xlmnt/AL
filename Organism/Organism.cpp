//
// Created by u on 21.11.21.
//

#include "Organism.h"
#include <utility>

OrganismStep Organism::update() {
    auto uptake = Uptake{this->f_uptake(this->uptake_coeff, this->size * this->size_multiplier)};
    return this->update(uptake);
}

OrganismStep Organism::update(double available_food) {
    auto uptake = Uptake{
        std::min(available_food, this->f_uptake(this->uptake_coeff, this->size * this->size_multiplier))
    };
    return update(uptake);
}

OrganismStep Organism::update(Uptake uptake) {
    bool ready_to_divide = false;

    if (this->alive){
        this->size += uptake.value;
        this->size -= this->f_metabolism(this->metabolism_coeff, this->size * this->size_multiplier);
    }
    if (this->size <= 0)
        this->alive = false;

    if (this->size >= this->division_threshold){
        ready_to_divide = true;
    }

    return OrganismStep{
            ready_to_divide,
            uptake.value
    };
}

Organism::Organism(std::string species, double size, double division_threshold, double uptake_coeff, double metabolism_coeff, double size_multiplier, std::function<double(double, double)> uptakeRate,
                   std::function<double(double, double)> metabolicRate): f_uptake(std::move(uptakeRate)), f_metabolism(std::move(metabolicRate)) {

    this->species = std::move(species);
    this->size = size;
    this->division_threshold = division_threshold;
    this->uptake_coeff = uptake_coeff;
    this->metabolism_coeff = metabolism_coeff;
    this->size_multiplier = size_multiplier;

    auto rd = std::random_device{};
    this->mut_rng = std::default_random_engine { rd() };
}

double Organism::get_size() const {
    return this->size;
}

bool Organism::is_alive() const {
    return this->alive;
}

void Organism::divide(std::vector<Organism>* vec) {

    auto org1 = Organism{
            this->species,
            this->size / 2.0,
            this->division_threshold,
            this->uptake_coeff,
            this->metabolism_coeff,
            this->size_multiplier,
            this->f_metabolism,
            this->f_uptake
    };
    this->number_of_divisions++;
    org1.set_number_of_divisions(this->number_of_divisions);
    org1.set_mutations(this->mutations);

    auto org2 = org1;

    org1.mutate();
    org2.mutate();

    vec->push_back(org1);
    vec->push_back(org2);
}

std::string Organism::get_name() {
    return this->species;
}

Mutation Organism::get_mutation() {

    std::uniform_real_distribution<> threshold(0.0, 1.0);
    auto rd = std::random_device();
    this->mut_rng = std::default_random_engine{ rd() };
    if (threshold(mut_rng) > MUTATION_CHANCE) {
        return Mutation{
            MutationType::NONE,
            0.0
        };
    }

    std::uniform_int_distribution<> get_mutation_type(1, 4);
    auto mtype = static_cast<MutationType>(get_mutation_type(mut_rng));

    double floor = 0.0;
    double cap = 0.0;


    switch (mtype) {
        case MutationType::C_METABOLISM:
            cap = MUTATION_MAGNITUDE_METABOLISM;
            break;
        case MutationType::DIV_THRESHOLD:
            cap = MUTATION_MAGNITUDE_DIV_TRESHOLD;
            break;
        case MutationType::C_UPTAKE:
            cap = MUTATION_MAGNITUDE_UPTAKE;
            break;
        case MutationType::SIZE_MULTIPLIER:
            floor = 1.0;
            cap = floor + MUTATION_MAGNITUDE_SIZE_MUL;
            break;
    }

    std::uniform_real_distribution<> dist(floor, cap);
    auto value = dist(mut_rng);

    return Mutation{
            mtype,
            value - 0.5 * (cap - floor)
    };
}

void Organism::mutate(Mutation mutation) {

    switch (mutation.type) {
        case MutationType::C_UPTAKE:
            this->uptake_coeff += mutation.value;
            break;
        case MutationType::C_METABOLISM:
            this->metabolism_coeff += mutation.value;
            break;
        case MutationType::DIV_THRESHOLD:
            this->division_threshold += mutation.value;
            break;
        case MutationType::SIZE_MULTIPLIER:
            this->size_multiplier += mutation.value;
            break;
        case MutationType::NONE:
            break;
    }

}

Mutation Organism::mutate() {
    auto mut = this->get_mutation();
    this->mutate(mut);

    if (mut.type != MutationType::NONE){
        this->mutations.push_back(mut);
    }

    return mut;
}

std::vector<Mutation> Organism::get_mutations() {
    return this->mutations;
}

size_t Organism::get_number_of_divisions() {
    return this->number_of_divisions;
}

void Organism::set_number_of_divisions(size_t num) {
    this->number_of_divisions = num;
}

void Organism::set_mutations(std::vector<Mutation> vec) {
    this->mutations = vec;
}
